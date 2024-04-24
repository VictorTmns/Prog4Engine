#pragma once
#pragma warning (push)
#pragma warning (disable: 4996)
#include "steam_api.h"
#pragma warning (pop)

namespace minigin
{
struct Achievement;


class CSteamAchievements
{
private:
	int64 m_iAppID; // Our current AppID
	Achievement* m_pAchievements; // Achievements data
	int m_iNumAchievements; // The number of Achievements
	bool m_bInitialized; // Have we called Request stats and received the callback?

public:
	CSteamAchievements();
	~CSteamAchievements();

	void AddAchievements(Achievement* Achievements, int NumAchievements);

	bool RequestStats();
	bool SetAchievement(const char* ID);
	bool ResetAchievement(const char* ID);

	bool AchievementCompleted(int idx);

	STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
		m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
		m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
		UserAchievementStored_t, m_CallbackAchievementStored);
};
}