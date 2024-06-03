#include "AchievementManager.h"

#include <utility>
#include "CSteamAchievements.h"



vic::AchievementManager::AchievementManager()
	: m_SteamApi{ std::make_unique<CSteamAchievements>() }
{
}


void vic::AchievementManager::AddAchievements(std::vector<Achievement>&& achievements)
{
	m_Achievements = std::move(achievements);
	m_SteamApi->AddAchievements(m_Achievements.data(), static_cast<int>(m_Achievements.size()));
}

void vic::AchievementManager::Update()
{
	SteamAPI_RunCallbacks();
}

vic::AchievementManager::~AchievementManager()
{

}

void vic::AchievementManager::Notify(Event event, const vic::BaseComponent* subject)
{
	for (const auto& achievement : m_Achievements)
	{
		if (achievement.event == event && achievement.predicate(subject))
		{
			m_SteamApi->SetAchievement(achievement.rgchName);
		}
	}

}
