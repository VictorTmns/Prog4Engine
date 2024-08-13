#pragma once
#include "BaseState.h"
#include "Scene.h"
#include "GameManager.h"

class MenuState final :
    public BaseState
{
public:
	MenuState();
	~MenuState();

	std::unique_ptr<BaseState> Update() override;

private:
	vic::Scene* m_MenuScene = nullptr;

	GameManager::PlayMode m_SelectedMode;
};

