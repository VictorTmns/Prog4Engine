#include "PlayingState.h"

#include "ReadLevelFromFile.h"


PlayingState::PlayingState(GameManager::PlayMode mode)
	: m_CurrentLevel{ 0 }
	, m_Mode{mode}
{
	m_Levels.emplace_back(vic::SceneManager::GetInstance().CreateScene("level1"), "../Data/Tron/Levels/level1.txt");
	m_Levels.emplace_back(vic::SceneManager::GetInstance().CreateScene("level2"), "../Data/Tron/Levels/level2.txt");
	m_Levels.emplace_back(vic::SceneManager::GetInstance().CreateScene("level3"), "../Data/Tron/Levels/level3.txt");

	SetLevel(m_CurrentLevel);
}

PlayingState::~PlayingState()
{
	for (const auto& level : m_Levels)
		level.first->Disable();
}

std::unique_ptr<BaseState> PlayingState::Update()
{
	return nullptr;
}

void PlayingState::Notify(Event event, const vic::BaseComponent* component)
{
	switch (event)
	{
	case Event::enemyDied:
		HandleEnemyDiedEvent(component);
		break;
	}
}

void PlayingState::IncrementLevel()
{
	m_CurrentLevel++;

	if (m_CurrentLevel >= static_cast<int>(m_Levels.size()))
		m_CurrentLevel -= static_cast<int>(m_Levels.size());

	SetLevel(m_CurrentLevel);
}

void PlayingState::SetLevel(int idx)
{
	m_Levels[idx].first->DeleteAll();
	for (auto& level : m_Levels)
		level.first->Disable();

	m_Levels[idx].first->Enable();
	ReadLevelFromFile(m_Levels[idx].first, m_Levels[idx].second, this, m_EnemiesRemaining, m_Mode);
}

void PlayingState::HandleEnemyDiedEvent(const vic::BaseComponent* enemyLogic)
{
	if (enemyLogic->Owner()->GetName() == "bluetank")
		m_Score += 100;
	else if (enemyLogic->Owner()->GetName() == "recognizer")
		m_Score += 250;


	m_EnemiesRemaining--;
	if(m_EnemiesRemaining <= 0)
	{
		IncrementLevel();
	}
}
