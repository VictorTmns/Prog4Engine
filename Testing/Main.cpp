#include "SDL.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#pragma warning (push)
#pragma warning (disable: 4996)
#pragma warning (pop)

#include "Minigin.h"
#include "Scene.h"
#include "ResourceManager.h"

#include "CircleRenderComponent.h"
#include "FPSComponent.h"
#include "InputManager.h"
#include "KeyboardTestComponent.h"
#include "LivesComponent.h"
#include "LivesDisplayComponent.h"
#include "OrbitComponent.h"
#include "PlaySoundComponent.h"
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "ScoreTestComponent.h"
#include "TextRenderComponent.h"
#include "TextureRenderComponent.h"
#include "ThrashTheCacheComponent.h"

void MakePlayer1(minigin::Scene* scene, minigin::Minigin* engine, minigin::Font* font, minigin::Font* smallFont);
void MakePlayer2(minigin::Scene* scene, minigin::Minigin* engine, minigin::Font* font, minigin::Font* smallFont);
void MakeManuel(minigin::Scene* scene, minigin::Minigin* engine, minigin::Font* font, minigin::Font* smallFont);

void load(minigin::Minigin* engine)
{
	[[maybe_unused]] auto& inputManager = minigin::InputManager::GetInstance();
	auto scene = minigin::SceneManager::GetInstance().CreateScene("Demo");
	auto font = minigin::ResourceManager::GetInstance().GetFont("Lingua.otf", 36);
	auto smallFont = minigin::ResourceManager::GetInstance().GetFont("Lingua.otf", 15);
	auto achievementsManager = engine->GetAchievementManager();

	std::function func = [](const minigin::BaseComponent* subject)
		{
			return (dynamic_cast<const ScoreComponent*>(subject)->GetScore() >= 500);
		};

	std::vector<minigin::Achievement> achievements{
		minigin::Achievement{0, std::string{"ACH_WIN_ONE_GAME"}, func, minigin::Observer::Event::scoreChange}
	};
	achievementsManager->AddAchievements(std::move(achievements));

	// FPS GAME OBJECT
	auto go = std::make_unique<minigin::GameObject>();
	go->AddComponent<minigin::FPSComponent>(font);
	go->SetLocalTranslate(20.f, 430.f);
	scene->AddGameObject(std::move(go));

	// DAE LOGO
	go = std::make_unique<minigin::GameObject>();
	auto texture = go->AddComponent<minigin::TextureRenderComponent>();
	texture->SetTexture("logo.tga");
	go->SetLocalTranslate(216, 180);
	scene->AddGameObject(std::move(go));

	// TEXT
	go = std::make_unique<minigin::GameObject>();
	go->AddComponent<minigin::TextRenderComponent>(font, "Programming 4 Assignment");
	go->SetLocalTranslate(80, 20);
	scene->AddGameObject(std::move(go));


	MakePlayer1(scene, engine, font, smallFont);
	MakePlayer2(scene, engine, font, smallFont);
	MakeManuel(scene, engine, font, smallFont);
}

void MakePlayer1(minigin::Scene* scene, minigin::Minigin* engine, [[maybe_unused]] minigin::Font* font, minigin::Font* smallFont)
{
	auto& inputManager = minigin::InputManager::GetInstance();

	//PLAYER CHARACTER
	auto go = std::make_unique<minigin::GameObject>();
	go->SetLocalTranslate(100, 230);

	go->AddComponent<CircleRenderComponent>(10.f, SDL_Color{ 255, 255, 0, 255 });


	KeyboardTestComponent* actorComponent = go->AddComponent<KeyboardTestComponent>();
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>(std::bind(&KeyboardTestComponent::Move, actorComponent, -1.f, 0.f)),
		SDLK_a,
		minigin::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>(std::bind(&KeyboardTestComponent::Move, actorComponent, 0.f, 1.f)),
		SDLK_s,
		minigin::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>(std::bind(&KeyboardTestComponent::Move, actorComponent, 0.f, -1.f)),
		SDLK_w,
		minigin::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::bind(&KeyboardTestComponent::Move, actorComponent, 1.f, 0.f),
		SDLK_d,
		minigin::ClickType::hold);



	minigin::LivesComponent* livesComponent = go->AddComponent<minigin::LivesComponent>(3);
	inputManager.BindToKeyboard(livesComponent,
		std::bind(&minigin::LivesComponent::TakeDamage, livesComponent),
		SDLK_p,
		minigin::ClickType::pressed);


	ScoreComponent* scoreComponent = go->AddComponent<ScoreComponent>();
	scoreComponent->AttachObserver(engine->GetAchievementManager());

	ScoreTestComponent* scoreTestComponent = go->AddComponent<ScoreTestComponent>(scoreComponent);
	inputManager.BindToKeyboard(scoreTestComponent,
		std::bind(&ScoreTestComponent::PickUpItem, scoreTestComponent),
		SDLK_o,
		minigin::ClickType::pressed);
	inputManager.BindToKeyboard(scoreTestComponent,
		std::bind(&ScoreTestComponent::KillEnemy, scoreTestComponent),
		SDLK_i,
		minigin::ClickType::pressed);

	// SOUND COMPONENT
	PlaySoundComponent* comp = go->AddComponent<PlaySoundComponent>();
	inputManager.BindToKeyboard(comp, 
		std::bind(&PlaySoundComponent::PlaySound, comp),
		SDLK_t,
		minigin::ClickType::pressed);


	scene->AddGameObject(std::move(go));


	go = std::make_unique<minigin::GameObject>();
	minigin::GameObject* goHolderPtr = go.get();
	go->SetLocalTranslate(0, 200);
	scene->AddGameObject(std::move(go));


	// LIVES DISPLAY 1
	go = std::make_unique<minigin::GameObject>();
	go->SetParent(goHolderPtr, false);
	minigin::LivesDisplayComponent* livesDisplay = go->AddComponent<minigin::LivesDisplayComponent>(smallFont);
	livesComponent->AttachObserver(livesDisplay);

	scene->AddGameObject(std::move(go));

	// SCORE DISPLAY 1
	go = std::make_unique<minigin::GameObject>();
	go->SetParent(goHolderPtr, false);
	go->SetLocalTranslate(0, 15);
	minigin::ScoreDisplayComponent* scoreDisplay = go->AddComponent<minigin::ScoreDisplayComponent>(smallFont);
	scoreComponent->AttachObserver(scoreDisplay);

	


	scene->AddGameObject(std::move(go));
}

void MakePlayer2(minigin::Scene* scene, minigin::Minigin* engine, [[maybe_unused]] minigin::Font* font, minigin::Font* smallFont)
{
	auto& inputManager = minigin::InputManager::GetInstance();

	// PLAYER CHARACTER 2
	auto go = std::make_unique<minigin::GameObject>();
	go->SetLocalTranslate(80, 300);

	go->AddComponent<CircleRenderComponent>(10.f, SDL_Color{ 255, 255, 0, 255 });

	KeyboardTestComponent* newComponent = go->AddComponent<KeyboardTestComponent>();
	inputManager.BindToControllerThumbStick(
		newComponent,
		std::bind_front(&KeyboardTestComponent::Move, newComponent),
		0,
		true);



	minigin::LivesComponent* livesComponent = go->AddComponent<minigin::LivesComponent>(3);
	inputManager.BindToKeyboard(livesComponent,
		std::bind(&minigin::LivesComponent::TakeDamage, livesComponent),
		SDLK_m,
		minigin::ClickType::pressed);


	ScoreComponent* scoreComponent = go->AddComponent<ScoreComponent>();
	scoreComponent->AttachObserver(engine->GetAchievementManager());

	ScoreTestComponent* scoreTestComponent = go->AddComponent<ScoreTestComponent>(scoreComponent);
	inputManager.BindToKeyboard(scoreTestComponent,
		std::bind(&ScoreTestComponent::PickUpItem, scoreTestComponent),
		SDLK_k,
		minigin::ClickType::pressed);
	inputManager.BindToKeyboard(scoreTestComponent,
		std::bind(&ScoreTestComponent::KillEnemy, scoreTestComponent),
		SDLK_l,
		minigin::ClickType::pressed);

	scene->AddGameObject(std::move(go));


	go = std::make_unique<minigin::GameObject>();
	minigin::GameObject* goHolderPtr = go.get();
	go->SetLocalTranslate(0, 240);
	scene->AddGameObject(std::move(go));


	// LIVES DISPLAY 2
	go = std::make_unique<minigin::GameObject>();
	go->SetParent(goHolderPtr, false);
	minigin::LivesDisplayComponent* livesDisplay = go->AddComponent<minigin::LivesDisplayComponent>(smallFont);
	livesComponent->AttachObserver(livesDisplay);

	scene->AddGameObject(std::move(go));

	// SCORE DISPLAY 2
	go = std::make_unique<minigin::GameObject>();
	go->SetParent(goHolderPtr, false);
	go->SetLocalTranslate(0, 15);
	minigin::ScoreDisplayComponent* scoreDisplay = go->AddComponent<minigin::ScoreDisplayComponent>(smallFont);
	scoreComponent->AttachObserver(scoreDisplay);

	scene->AddGameObject(std::move(go));

}

void MakeManuel(minigin::Scene* scene, [[maybe_unused]] minigin::Minigin* engine, [[maybe_unused]] minigin::Font* font, minigin::Font* smallFont)
{
	auto go = std::make_unique<minigin::GameObject>();
	auto goHolder = go.get();
	go->SetLocalTranslate(300, 80);
	scene->AddGameObject(std::move(go));

	go = std::make_unique<minigin::GameObject>();
	go->AddComponent<minigin::TextRenderComponent>(
		smallFont, "use the WASD to move the first player, use P to to take damage and I&O to get points",
		minigin::TextRenderComponent::TextAlignment::left);
	go->SetParent(goHolder);
	scene->AddGameObject(std::move(go));

	go = std::make_unique<minigin::GameObject>();
	go->SetLocalTranslate(10, 20);
	go->AddComponent<minigin::TextRenderComponent>(
		smallFont, "use the D-Pad to move the second player, use M to to take damage and K&L to get points",
		minigin::TextRenderComponent::TextAlignment::left);
	go->SetParent(goHolder);
	scene->AddGameObject(std::move(go));

}


int main(int, char* []) {


	minigin::Minigin engine("../Data/Testing/");
	engine.Run(load);


	return 0;
}