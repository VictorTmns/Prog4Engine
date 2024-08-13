#pragma once
#include "BaseState.h"
#include "Scene.h"

class MenuState final :
    public BaseState
{
public:
	MenuState();

	std::unique_ptr<BaseState> Update() override;

private:
	vic::Scene* m_MenuScene = nullptr;
};

