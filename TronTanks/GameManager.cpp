#include "GameManager.h"

#include "HighScoreState.h"
#include "PlayingState.h"

GameManager::GameManager(vic::GameObject* owner)
	: BaseComponent{owner}
	, m_State{std::make_unique<MenuState>()}

{
}

void GameManager::Update()
{
	std::unique_ptr<BaseState> newState = m_State->Update();

	if(newState != nullptr)
	{
		m_State = std::move(newState);
	}
}

