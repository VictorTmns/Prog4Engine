#include "AchievementManager.h"

#include "BaseComponent.h"
#include "ScoreComponent.h"

std::vector<Achievement_t> AchievementManager::m_Achievements
{
	_ACH_ID(WinAGame, "ACH_WIN_ONE_GAME"),
};

AchievementManager::AchievementManager()
	: m_SteamApi{ new CSteamAchievements(m_Achievements.data(), static_cast<int>(m_Achievements.size())) }
{
}

void AchievementManager::RemoveAchievements()
{
	for (const auto& achievement : m_Achievements)
	{
		m_SteamApi->ResetAchievement(achievement.m_pchAchievementID);
	}
}

AchievementManager::~AchievementManager()
{

}

void AchievementManager::Notify(Event event, const minigin::BaseComponent* subject)
{
	switch (event) {
	case Event::scoreChange:
		if(dynamic_cast<const ScoreComponent*>(subject)->GetScore() >= 500)
			m_SteamApi->SetAchievement("ACH_WIN_ONE_GAME");
		break;
	default: ;
	}
}
