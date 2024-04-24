#pragma once
#include <memory>
#include <vector>
#include "Observer.h"
#include <functional>
#include "BaseComponent.h"
#include "Observer.h"

namespace minigin
{
class CSteamAchievements;

struct Achievement
{
	int achievementID;
	const char* pchAchievementID;
	char rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
	std::function<bool(Observer::Event, const BaseComponent*)> predicate;
};

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
class AchievementManager : public Observer
{
public:
	AchievementManager();
	void AddAchievements(std::vector<Achievement> achievements);
	~AchievementManager() override;
	void Notify(Event event, const BaseComponent* subject) override;

private:


	enum class Achievements
	{
		WinAGame = 0,
	};

	std::unique_ptr<CSteamAchievements> m_SteamApi;
	static std::vector<Achievement> m_Achievements;
};
}