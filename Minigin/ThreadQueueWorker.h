#pragma once
#include <functional>
#include <mutex>
#include <thread>
#include <queue>

namespace minigin
{


template <typename Task>
class ThreadQueueWorker
{
public:
	explicit ThreadQueueWorker(std::function<bool(const Task&)> taskProcessFunc);
	~ThreadQueueWorker();

	ThreadQueueWorker(const ThreadQueueWorker& other) = delete;
	ThreadQueueWorker(ThreadQueueWorker&& other) noexcept = delete;
	ThreadQueueWorker& operator=(const ThreadQueueWorker& other) = delete;
	ThreadQueueWorker& operator=(ThreadQueueWorker&& other) noexcept = delete;

	void AddTask(Task&& task);

private:
	void TaskProcessor();

	std::jthread m_JThread;

	bool m_EndThread = false;

	std::function<bool(const Task&)> m_TaskProcesFunc;
	std::queue<Task> m_TaskQueue;

	std::mutex m_Mutex;
	std::condition_variable m_WorkAvailableSignal;
};
}

//IMPLEMENTATION

namespace minigin
{

	template<typename Task>
	ThreadQueueWorker<Task>::ThreadQueueWorker(std::function<bool(const Task&)> taskProcessFunc)
		: m_JThread{}
		, m_EndThread{ false }
		, m_TaskProcesFunc{ taskProcessFunc }
	{
		m_JThread = std::jthread{ [this](){this->TaskProcessor(); } };
	}

	template <typename Task>
	ThreadQueueWorker<Task>::ThreadQueueWorker::~ThreadQueueWorker()
	{
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_EndThread = true;
		}
		m_WorkAvailableSignal.notify_one();
		m_JThread.join();
	}

	template <typename Task>
	void ThreadQueueWorker<Task>::AddTask(Task&& task)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_TaskQueue.push(task);
		m_WorkAvailableSignal.notify_one();
	}

	template <typename Task>
	void ThreadQueueWorker<Task>::TaskProcessor()
	{
		while (!m_EndThread)
		{
			std::unique_lock lock(m_Mutex);
			m_WorkAvailableSignal.wait(lock,
				[this]() { return !m_TaskQueue.empty() || m_EndThread; });

			if (m_EndThread) {
				break;
			}

			while (!m_TaskQueue.empty())
			{
				m_TaskProcesFunc(m_TaskQueue.front());
				m_TaskQueue.pop();
			}
		}
	}

}