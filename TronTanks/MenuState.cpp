#include "MenuState.h"

#include "InputManager.h"
#include "PlayingState.h"
#include "SceneManager.h"
#include "TextRenderComponent.h"

MenuState::MenuState()
	: m_ModePrimRenderComponent{nullptr}, m_SelectedMode{GameManager::PlayMode::singleplayer}
{
	m_MenuScene = vic::SceneManager::GetInstance().CreateScene("menu");

	const int menuSize{40};
	vic::Font* titleFont = vic::ResourceManager::GetInstance().LoadFont("Fonts/TRON.TTF", menuSize);
	vic::Font* simpleFont = vic::ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 30);
	vic::Font* simpleSmallFont = vic::ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 20);


	vic::GameObject& titleGO = m_MenuScene->CreateGameObject("title");
	titleGO.GetTransform().SetWorldPosition(320, 10);

	titleGO.AddComponent<vic::TextRenderComponent>(titleFont, "TRON:", vic::Font::TextAlignment::center);
	titleGO.AddComponent<vic::TextRenderComponent>(titleFont, "BATTLE TANKS", vic::Font::TextAlignment::center)
	       ->SetOffset(glm::vec2{0, menuSize});


	vic::GameObject& starttext = m_MenuScene->CreateGameObject();
	starttext.GetTransform().SetWorldPosition(320, 200);
	starttext.AddComponent<vic::TextRenderComponent>(simpleFont, "Press Space or A", vic::Font::TextAlignment::center);
	starttext.AddComponent<vic::TextRenderComponent>(simpleFont, "to Start", vic::Font::TextAlignment::center)
	         ->SetOffset(glm::vec2{0, 30});;


	vic::GameObject& modeText = m_MenuScene->CreateGameObject();
	modeText.GetTransform().SetWorldPosition(320, 300);
	modeText.AddComponent<vic::TextRenderComponent>(simpleFont, "Press tab or Y", vic::Font::TextAlignment::center);
	modeText.AddComponent<vic::TextRenderComponent>(simpleFont, "to change play mode", vic::Font::TextAlignment::center)
	        ->SetOffset(glm::vec2{0, 30});


	vic::GameObject& modeSelectedText = m_MenuScene->CreateGameObject();
	modeSelectedText.GetTransform().SetWorldPosition(320, 380);
	m_ModeRenderComponent = modeSelectedText.AddComponent<vic::TextRenderComponent>(
		simpleSmallFont, "singlePlayer", vic::Font::TextAlignment::center);
}

MenuState::~MenuState()
{
	m_MenuScene->Disable();
}

std::unique_ptr<BaseState> MenuState::Update()
{
	if (vic::InputManager::GetInstance().KeyDown(SDLK_LSHIFT)
		|| vic::InputManager::GetInstance().KeyDown(SDLK_RSHIFT)
		|| vic::InputManager::GetInstance().ButtonDown(0, vic::ControllerButton::y))
	{
		switch (m_SelectedMode)
		{
		case GameManager::PlayMode::singleplayer:
			m_SelectedMode = GameManager::PlayMode::multiplayer;
			m_ModeRenderComponent->SetText("multiplayer");
			break;
		case GameManager::PlayMode::multiplayer:
			m_SelectedMode = GameManager::PlayMode::versus;
			m_ModeRenderComponent->SetText("versus");
			break;
		case GameManager::PlayMode::versus:
			m_SelectedMode = GameManager::PlayMode::singleplayer;
			m_ModeRenderComponent->SetText("singleplayer");
			break;
		default: ;
		}
	}

	if (vic::InputManager::GetInstance().KeyDown(SDLK_SPACE)
		|| vic::InputManager::GetInstance().ButtonDown(0, vic::ControllerButton::a))
		return std::make_unique<PlayingState>(m_SelectedMode);

	return nullptr;
}
