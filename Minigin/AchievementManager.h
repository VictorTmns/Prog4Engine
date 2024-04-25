#pragma once
#include <memory>
#include <vector>
#include "Observer.h"
#include <functional>
#include <string>

#include "BaseComponent.h"

namespace minigin
{
class CSteamAchievements;

struct Achievement
{
	Achievement(int id, std::string charID, const std::function<bool(const BaseComponent*)>& condition, Observer::Event event)
		: achievementID{id}, pchAchievementID{charID}, rgchName{}, rgchDescription{}, bAchieved{false}, iIconImage{0},
		  predicate{condition}, event{event}
	{
	}

	Achievement() = delete;
	int achievementID;
	std::string pchAchievementID;
	char rgchName[128];
	char rgchDescription[256];
	bool bAchieved;
	int iIconImage;
	std::function<bool(const BaseComponent*)> predicate;
	Observer::Event event;
};

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

class AchievementManager : public Observer
{
public:
	AchievementManager();
	void AddAchievements(std::vector<Achievement>&& achievements);
	~AchievementManager() override;
	void Notify(Event event, const BaseComponent* subject) override;

private:

	std::unique_ptr<CSteamAchievements> m_SteamApi;
	std::vector<Achievement> m_Achievements;
};
}