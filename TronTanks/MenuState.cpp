#include "MenuState.h"

#include "SceneManager.h"
#include "TextRenderComponent.h"

MenuState::MenuState()
{
	m_MenuScene = vic::SceneManager::GetInstance().CreateScene("menu");

	const int menuSize{ 40 };
	vic::Font* titleFont = vic::ResourceManager::GetInstance().LoadFont("Fonts/TRON.TTF", menuSize);
	vic::GameObject& titleGO = m_MenuScene->CreateGameObject("title");
	titleGO.GetTransform().SetWorldPosition(320, 10);

	titleGO.AddComponent<vic::TextRenderComponent>(titleFont, "TRON:", vic::Font::TextAlignment::center);
	titleGO.AddComponent<vic::TextRenderComponent>(titleFont, "BATTLE TANKS", vic::Font::TextAlignment::center)
		->SetOffset(glm::vec2{0, menuSize });
}

std::unique_ptr<BaseState> MenuState::Update()
{

	return nullptr;
}
