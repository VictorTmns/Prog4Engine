#pragma once
#include <memory>
#include <vector>

#include "CSteamAchievements.h"
#include "Observer.h"

class AchievementManager : public minigin::Observer
{
public:
	AchievementManager();
	void RemoveAchievements();
	~AchievementManager() override;
	void Notify(Event event, const minigin::BaseComponent* subject) override;
private:
	enum Achievements
	{
		WinAGame = 0,
	};

	std::unique_ptr<CSteamAchievements> m_SteamApi;
	static std::vector<Achievement_t> m_Achievements;
};
