#include "PlayingState.h"

#include "Font.h"
#include "HighScoreState.h"
#include "ReadLevelFromFile.h"


PlayingState::PlayingState(GameManager::PlayMode mode)
	: m_CurrentLevel{ 0 }
	, m_Mode{mode}
{
	m_Hud = vic::SceneManager::GetInstance().CreateScene("hud");

	vic::Font* scoreFont{ vic::ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 20)};
	vic::GameObject& scoreGO{ m_Hud->CreateGameObject() };
	scoreGO.GetTransform().SetWorldPosition(20, 20);
	m_ScoreRenderComponent = scoreGO.AddComponent<vic::TextRenderComponent>(scoreFont, "score: 0", vic::Font::TextAlignment::left);
	

	m_Levels.emplace_back(vic::SceneManager::GetInstance().CreateScene("level1"), "../Data/Tron/Levels/level1.txt");
	m_Levels.emplace_back(vic::SceneManager::GetInstance().CreateScene("level2"), "../Data/Tron/Levels/level2.txt");
	m_Levels.emplace_back(vic::SceneManager::GetInstance().CreateScene("level3"), "../Data/Tron/Levels/level3.txt");

	SetLevel(m_CurrentLevel);
}

PlayingState::~PlayingState()
{
	m_Hud->Disable();
	for (const auto& level : m_Levels)
		level.first->Disable();
}

std::unique_ptr<BaseState> PlayingState::Update()
{
	if (m_ShowHighScore)
		return std::make_unique<HighScoreState>();

	if (m_ReloadLevel)
	{
		m_ReloadLevel = false;
		SetLevel(m_CurrentLevel);
	}

	return nullptr;
}

void PlayingState::CleanupLevel()
{
	m_Levels[m_CurrentLevel].first->DeleteAll();
	for (auto& level : m_Levels)
		level.first->Disable();
}

void PlayingState::Notify(Event event, const vic::BaseComponent* component)
{
	switch (event)
	{
	case Event::enemyDied:
		HandleEnemyDiedEvent(component);
		break;
	case Event::playerHit:
		CleanupLevel();
		m_LivesLeft--;
		if (m_LivesLeft >= 0)
			m_ReloadLevel = true;
		else
			m_ShowHighScore = true;
		break;
	}
}

void PlayingState::IncrementLevel()
{
	m_CurrentLevel++;

	if (m_CurrentLevel >= static_cast<int>(m_Levels.size()))
		m_CurrentLevel -= static_cast<int>(m_Levels.size());
}

void PlayingState::SetLevel(int idx)
{
	m_Levels[idx].first->Enable();

	glm::vec2 levelSize{};
	ReadLevelFromFile(m_Levels[idx].first, glm::vec2{ 60, 60 }, m_Levels[idx].second, this, m_Mode, m_EnemiesRemaining, levelSize);
	m_Levels[idx].first->ResetFirstAction();
}

void PlayingState::HandleEnemyDiedEvent(const vic::BaseComponent* enemyLogic)
{
	if (enemyLogic->Owner()->GetName() == "blueTank")
		m_Score += 100;
	else if (enemyLogic->Owner()->GetName() == "recognizer")
		m_Score += 250;

	m_ScoreRenderComponent->SetText("score: " + std::to_string(m_Score));

	m_EnemiesRemaining--;
	if(m_EnemiesRemaining <= 0)
	{
		IncrementLevel();
		SetLevel(m_CurrentLevel);
	}
}
