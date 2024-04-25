#include "CSteamAchievements.h"
#include "AchievementManager.h"
#include <SDL_syswm.h>
#include <iostream>

minigin::CSteamAchievements::CSteamAchievements() :
    m_iAppID(0),
    m_pAchievements{},
    m_iNumAchievements{},
    m_bInitialized(false),
    m_CallbackUserStatsReceived(this, &CSteamAchievements::OnUserStatsReceived),
    m_CallbackUserStatsStored(this, &CSteamAchievements::OnUserStatsStored),
    m_CallbackAchievementStored(this, &CSteamAchievements::OnAchievementStored)
{
	if (!SteamAPI_Init())
	{
		throw std::runtime_error("Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).");
	}

	std::cout << "Successfully initialized steam." << std::endl;

    m_iAppID = SteamUtils()->GetAppID();
}

minigin::CSteamAchievements::~CSteamAchievements()
{

	SteamAPI_Shutdown();
}

void minigin::CSteamAchievements::AddAchievements(Achievement* Achievements, int NumAchievements)
{
	m_pAchievements = Achievements;
	m_iNumAchievements = NumAchievements;
	RequestStats();
}

bool minigin::CSteamAchievements::RequestStats()
{
	// Is Steam loaded? If not we can't get stats.
	if (NULL == SteamUserStats() || NULL == SteamUser())
	{
		return false;
	}
	// Is the user logged on?  If not we can't get stats.
	if (!SteamUser()->BLoggedOn())
	{
		return false;
	}
	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}

bool minigin::CSteamAchievements::SetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_bInitialized)
	{
		SteamUserStats()->SetAchievement(ID);
		const auto result = SteamUserStats()->StoreStats();
		RequestStats();
		return result;
	}
	// If not then we can't set achievements yet
	return false;
}

bool minigin::CSteamAchievements::ResetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_bInitialized)
	{
		// Check if the achievement is already achieved
		if (SteamUserStats()->GetAchievement(ID, nullptr) == true)
		{
			// Achievement is already achieved, so we unlock it again
			SteamUserStats()->ClearAchievement(ID);
			const auto result = SteamUserStats()->StoreStats();
			RequestStats();
			return result == true; // Return true if clearing and storing stats succeeds
		}
	}
	// If achievement is not achieved or Steam not initialized, return false
	return false;
}

bool minigin::CSteamAchievements::AchievementCompleted(int idx)
{
	return m_pAchievements[idx].bAchieved;
}

void minigin::CSteamAchievements::OnUserStatsReceived(UserStatsReceived_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Received stats and achievements from Steam\n");
			m_bInitialized = true;

			// load achievements
			for (int iAch = 0; iAch < m_iNumAchievements; ++iAch)
			{
				Achievement& ach = m_pAchievements[iAch];

				SteamUserStats()->GetAchievement(ach.pchAchievementID.data(), &ach.bAchieved);
				_snprintf_s(ach.rgchName, sizeof(ach.rgchName), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.pchAchievementID.data(),
						"name"));
				_snprintf_s(ach.rgchDescription, sizeof(ach.rgchDescription), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.pchAchievementID.data(),
						"desc"));
			}
		}
		else
		{
			char buffer[128];
			_snprintf_s(buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}

void minigin::CSteamAchievements::OnUserStatsStored(UserStatsStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Stored stats for Steam\n");
		}
		else
		{
			char buffer[128];
			_snprintf_s(buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}

void minigin::CSteamAchievements::OnAchievementStored(UserAchievementStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
	{
		OutputDebugString("Stored Achievement for Steam\n");
	}
}