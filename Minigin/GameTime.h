#pragma once
#include <chrono>
#include <thread>

#include "BaseComponent.h"
#include "Singleton.h"

class GameTime : public vic::Singleton<GameTime>
{
public:
	void Init(double fixedTimeStep, int frameCap)
	{
		m_FixedTimeStep = fixedTimeStep;
		m_FrameCap = frameCap;
		m_Previous = std::chrono::high_resolution_clock::now();
	}

	void Update()
	{
		auto current = std::chrono::high_resolution_clock::now();
		m_DeltaTime = std::chrono::duration<double>(current - m_Previous).count();
		m_RemainingLag += m_DeltaTime;

		m_Previous = current;
	}

	float GetFps()
	{
		return static_cast<float>(1.0 / m_DeltaTime);
	}

	bool LagRemaining()
	{
		if(m_RemainingLag >= m_FixedTimeStep)
		{
			m_RemainingLag -= m_FixedTimeStep;
			return true;
		}

		return false;
	}

	double GetDeltaTime()
	{
		return m_DeltaTime;
	}

	double GetFixedTimeStep()
	{
		return m_FixedTimeStep;
	}

	std::chrono::milliseconds SleepTime()
	{
		auto minFrameTime = std::chrono::milliseconds(static_cast<long long>((1.0 / m_FrameCap) * 1000));
		auto sleepTime = m_Previous + minFrameTime -
			std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(sleepTime);
	}


private:
	std::chrono::time_point<std::chrono::steady_clock> m_Previous;

	double m_DeltaTime = 0.0;
	double m_FixedTimeStep = 0.02;
	double m_RemainingLag = 0.0;

	int m_FrameCap = 60;
};
