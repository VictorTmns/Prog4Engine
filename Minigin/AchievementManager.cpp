#include "AchievementManager.h"
#include "AchievementManager.h"
#include "CSteamAchievements.h"

std::vector<minigin::Achievement> minigin::AchievementManager::m_Achievements
{
	_ACH_ID(int(minigin::AchievementManager::Achievements::WinAGame), "ACH_WIN_ONE_GAME"),
};

minigin::AchievementManager::AchievementManager()
	: m_SteamApi{ std::make_unique<CSteamAchievements>() }
{
}


void minigin::AchievementManager::AddAchievements(std::vector<Achievement> achievements)
{

	m_SteamApi->AddAchievements(m_Achievements.data(), static_cast<int>(m_Achievements.size()));
}

minigin::AchievementManager::~AchievementManager()
{

}

void minigin::AchievementManager::Notify(Event event, const minigin::BaseComponent* subject)
{
	for (const auto& achievement : m_Achievements)
	{
		if (achievement.predicate(event, subject))
		{
			m_SteamApi->SetAchievement(achievement)
		}
	}

	for (const auto& achievement : m_Achievements)
	{
		if (achievement.predicate(event, subject))
		{
			m_SteamApi->SetAchievement(achievement.rgchName);
		}
	}
}
