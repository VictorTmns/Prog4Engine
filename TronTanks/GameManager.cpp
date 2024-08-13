#include "GameManager.h"

#include "PlayingState.h"

GameManager::GameManager(vic::GameObject* owner)
	: BaseComponent{owner}
	, m_State{std::make_unique<PlayingState>()}
{
}

void GameManager::Update()
{
	m_State->Update();
}

void GameManager::Notify(Event, const BaseComponent*)
{
	
}
