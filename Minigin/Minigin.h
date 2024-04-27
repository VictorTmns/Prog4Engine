#pragma once
#include <string>
#include <functional>

#include "AchievementManager.h"

namespace minigin
{
	class Minigin final
	{
	public:
		explicit Minigin(const std::string& resourceDataPath);
		~Minigin();
		void Run(const std::function<void(Minigin*)>& load);

		AchievementManager* GetAchievementManager() const;

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		void Init(const std::string& resourceDataPath);

		std::unique_ptr<AchievementManager> m_Achievement;
	};
}
