#pragma once
#include <chrono>

#include "BaseComponent.h"
#include "Singleton.h"

class Time : public minigin::Singleton<Time>
{
public:
	void Init(double fixedTimeStep)
	{
		m_FixedTimeStep = fixedTimeStep;
		previous = std::chrono::high_resolution_clock::now();
	}

	void Update()
	{
		auto current = std::chrono::high_resolution_clock::now();
		m_DeltaTime = std::chrono::duration<double>(current - previous).count();
		m_RemainingLag += m_DeltaTime;

		previous = current;
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


private:
	std::chrono::time_point<std::chrono::steady_clock> previous;

	double m_DeltaTime = 0.0;
	double m_FixedTimeStep = 0.02;
	double m_RemainingLag = 0.0;
};
