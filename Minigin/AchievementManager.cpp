#include "AchievementManager.h"

#include <utility>
#include "CSteamAchievements.h"



minigin::AchievementManager::AchievementManager()
	: m_SteamApi{ std::make_unique<CSteamAchievements>() }
{
}


void minigin::AchievementManager::AddAchievements(std::vector<Achievement>&& achievements)
{
	m_Achievements = std::move(achievements);
	m_SteamApi->AddAchievements(m_Achievements.data(), static_cast<int>(m_Achievements.size()));
}

void minigin::AchievementManager::Update()
{
	SteamAPI_RunCallbacks();
}

minigin::AchievementManager::~AchievementManager()
{

}

void minigin::AchievementManager::Notify(Event event, const minigin::BaseComponent* subject)
{
	for (const auto& achievement : m_Achievements)
	{
		if (achievement.event == event && achievement.predicate(subject))
		{
			m_SteamApi->SetAchievement(achievement.rgchName);
		}
	}

}
