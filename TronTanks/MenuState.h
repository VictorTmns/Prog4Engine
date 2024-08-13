#pragma once
#include "BaseState.h"
#include "Scene.h"
#include "GameManager.h"
#include "PrimitivesRenderComponent.h"
#include "TextRenderComponent.h"

class MenuState final :
    public BaseState
{
public:
	MenuState();
	~MenuState() override;

	std::unique_ptr<BaseState> Update() override;

private:
	vic::Scene* m_MenuScene = nullptr;


	vic::TextRenderComponent* m_ModeRenderComponent;
	vic::PrimitivesRenderComponent* m_ModePrimRenderComponent;
	GameManager::PlayMode m_SelectedMode;
};

