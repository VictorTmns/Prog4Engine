#pragma once
#include <functional>
#include <mutex>
#include <thread>
#include <queue>
#include <shared_mutex>

namespace vic
{


template <typename Task>

class ThreadTaskQueue
{
public:
	explicit ThreadTaskQueue(std::function<bool(const Task&)> taskProcessFunc);
	~ThreadTaskQueue();

	ThreadTaskQueue(const ThreadTaskQueue& other) = delete;
	ThreadTaskQueue(ThreadTaskQueue&& other) noexcept = delete;
	ThreadTaskQueue& operator=(const ThreadTaskQueue& other) = delete;
	ThreadTaskQueue& operator=(ThreadTaskQueue&& other) noexcept = delete;

	void AddTask(Task&& task) requires std::equality_comparable<Task>;

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

namespace vic
{

	template<typename Task>
	ThreadTaskQueue<Task>::ThreadTaskQueue(std::function<bool(const Task&)> taskProcessFunc)
		: m_JThread{}
		, m_EndThread{ false }
		, m_TaskProcesFunc{ taskProcessFunc }
	{
		m_JThread = std::jthread{ [this](){this->TaskProcessor(); } };
	}

	template <typename Task>
	ThreadTaskQueue<Task>::ThreadTaskQueue::~ThreadTaskQueue()
	{
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_EndThread = true;
		}
		m_WorkAvailableSignal.notify_one();
		m_JThread.join();
	}

	template <typename Task> 
	void ThreadTaskQueue<Task>::AddTask(Task&& task) requires std::equality_comparable<Task>
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_TaskQueue.empty() || m_TaskQueue.back() != task)
		{
			m_TaskQueue.push(task);
			m_WorkAvailableSignal.notify_one();
		}
	}

	template <typename Task>
	void ThreadTaskQueue<Task>::TaskProcessor()
	{
		while (!m_EndThread)
		{
			std::unique_lock lock(m_Mutex);
			m_WorkAvailableSignal.wait(lock,
				[this]() { return !m_TaskQueue.empty() || m_EndThread; });

			if (m_EndThread)
				break;
			

			while (!m_TaskQueue.empty())
			{
				auto task = m_TaskQueue.front();
				m_TaskQueue.pop();

				lock.unlock();
				m_TaskProcesFunc(task);
				lock.lock();
			}
		}
	}

}