#include "GameManager.h"

#include "PlayingState.h"

GameManager::GameManager(vic::GameObject* owner)
	: BaseComponent{owner}
	, m_State{std::make_unique<PlayingState>(PlayMode::singleplayer)}
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

void GameManager::Notify(Event, const BaseComponent*)
{
	
}
