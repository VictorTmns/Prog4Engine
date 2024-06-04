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
#include "Renderer.h"
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "ScoreTestComponent.h"
#include "TextRenderComponent.h"
#include "TextureRenderComponent.h"
#include "ThrashTheCacheComponent.h"

void MakePlayer1(vic::Scene* scene, vic::Minigin* engine, vic::Font* font, vic::Font* smallFont);
void MakePlayer2(vic::Scene* scene, vic::Minigin* engine, vic::Font* font, vic::Font* smallFont);
void MakeManuel(vic::Scene* scene, vic::Minigin* engine, vic::Font* font, vic::Font* smallFont);
void MakeRotatingBalls(vic::Scene* scene, vic::Minigin* engine);

void load(vic::Minigin* engine)
{
	[[maybe_unused]] auto& inputManager = vic::InputManager::GetInstance();
	auto scene = vic::SceneManager::GetInstance().CreateScene("Demo");
	auto font = vic::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto smallFont = vic::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	std::function func = [](const vic::BaseComponent* subject)
		{
			return (dynamic_cast<const ScoreComponent*>(subject)->GetScore() >= 500);
		};


	// FPS GAME OBJECT
	vic::GameObject& go = scene->CreateGameObject();
	go.AddComponent<vic::FPSComponent>(font);
	go.GetTransform().SetLocalPosition(20.f, 430.f);

	// DAE LOGO
	vic::GameObject& go2 = scene->CreateGameObject();
	auto texture = go2.AddComponent<vic::TextureRenderComponent>();
	texture->SetTexture("logo.tga");
	go2.GetTransform().SetLocalPosition(216, 180);

	// TEXT
	vic::GameObject& go3 = scene->CreateGameObject();
	go3.AddComponent<vic::TextRenderComponent>(font, "Programming 4 Assignment");
	go3.GetTransform().SetLocalPosition(80, 20);


	MakePlayer1(scene, engine, font, smallFont);
	MakePlayer2(scene, engine, font, smallFont);
	MakeManuel(scene, engine, font, smallFont);

	MakeRotatingBalls(scene, engine);
}

void MakePlayer1(vic::Scene* scene, vic::Minigin*, vic::Font*, vic::Font* smallFont)
{
	auto& inputManager = vic::InputManager::GetInstance();

	//PLAYER CHARACTER
	vic::GameObject& go{ scene->CreateGameObject() };
	go.GetTransform().SetLocalPosition(100, 230);

	go.AddComponent<CircleRenderComponent>(10.f, SDL_Color{ 255, 255, 0, 255 });


	KeyboardTestComponent* actorComponent = go.AddComponent<KeyboardTestComponent>();
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>([actorComponent] { actorComponent->Move(-1.f, 0.f); }),
		SDLK_a,
		vic::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>([actorComponent] { actorComponent->Move(0.f, 1.f); }),
		SDLK_s,
		vic::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>([actorComponent] { actorComponent->Move(0.f, -1.f); }),
		SDLK_w,
		vic::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		[actorComponent] { actorComponent->Move(1.f, 0.f); },
		SDLK_d,
		vic::ClickType::hold);



	LivesComponent* livesComponent = go.AddComponent<LivesComponent>(3);
	inputManager.BindToKeyboard(livesComponent,
		[livesComponent] { livesComponent->TakeDamage(); },
		SDLK_p,
		vic::ClickType::pressed);


	ScoreComponent* scoreComponent = go.AddComponent<ScoreComponent>();

	ScoreTestComponent* scoreTestComponent = go.AddComponent<ScoreTestComponent>(scoreComponent);
	inputManager.BindToKeyboard(scoreTestComponent,
		[scoreTestComponent] { scoreTestComponent->PickUpItem(); },
		SDLK_o,
		vic::ClickType::pressed);
	inputManager.BindToKeyboard(scoreTestComponent,
		[scoreTestComponent] { scoreTestComponent->KillEnemy(); },
		SDLK_i,
		vic::ClickType::pressed);

	// SOUND COMPONENT
	PlaySoundComponent* playSoundComponent = go.AddComponent<PlaySoundComponent>();
	inputManager.BindToKeyboard(playSoundComponent,
		[playSoundComponent] { playSoundComponent->PlaySound(); },
		SDLK_t,
		vic::ClickType::pressed);




	vic::GameObject& go2 = scene->CreateGameObject();
	go2.GetTransform().SetLocalPosition(0, 200);


	// LIVES DISPLAY 1
	vic::GameObject& go3 = scene->CreateGameObject();
	go3.SetParent(&go2, false);
	vic::LivesDisplayComponent* livesDisplay = go3.AddComponent<vic::LivesDisplayComponent>(smallFont);
	livesComponent->AttachObserver(livesDisplay);


	// SCORE DISPLAY 1
	vic::GameObject& go4 = scene->CreateGameObject();
	go4.SetParent(&go2, false);
	go4.GetTransform().SetLocalPosition(0, 15);
	ScoreDisplayComponent* scoreDisplay = go4.AddComponent<ScoreDisplayComponent>(smallFont);
	scoreComponent->AttachObserver(scoreDisplay);




}

void MakePlayer2(vic::Scene* scene, vic::Minigin*, vic::Font*, vic::Font* smallFont)
{
	auto& inputManager = vic::InputManager::GetInstance();

	// PLAYER CHARACTER 2
	vic::GameObject& go{ scene->CreateGameObject() };
	go.GetTransform().SetLocalPosition(80, 300);

	go.AddComponent<CircleRenderComponent>(10.f, SDL_Color{ 255, 255, 0, 255 });

	KeyboardTestComponent* newComponent = go.AddComponent<KeyboardTestComponent>();
	inputManager.BindToControllerThumbStick(
		newComponent,
		std::bind_front(&KeyboardTestComponent::Move, newComponent),
		0,
		true);



	LivesComponent* livesComponent = go.AddComponent<LivesComponent>(3);
	inputManager.BindToKeyboard(livesComponent,
		[livesComponent] { livesComponent->TakeDamage(); },
		SDLK_m,
		vic::ClickType::pressed);


	ScoreComponent* scoreComponent = go.AddComponent<ScoreComponent>();

	ScoreTestComponent* scoreTestComponent = go.AddComponent<ScoreTestComponent>(scoreComponent);
	inputManager.BindToKeyboard(scoreTestComponent,
		[scoreTestComponent] { scoreTestComponent->PickUpItem(); },
		SDLK_k,
		vic::ClickType::pressed);
	inputManager.BindToKeyboard(scoreTestComponent,
		[scoreTestComponent] { scoreTestComponent->KillEnemy(); },
		SDLK_l,
		vic::ClickType::pressed);



	vic::GameObject& go2{ scene->CreateGameObject() };
	go2.GetTransform().SetLocalPosition(0, 240);


	// LIVES DISPLAY 2
	vic::GameObject& go3{ scene->CreateGameObject() };
	go3.SetParent(&go2, false);
	vic::LivesDisplayComponent* livesDisplay = go3.AddComponent<vic::LivesDisplayComponent>(smallFont);
	livesComponent->AttachObserver(livesDisplay);


	// SCORE DISPLAY 2
	vic::GameObject& go4{ scene->CreateGameObject() };
	go4.SetParent(&go2, false);
	go4.GetTransform().SetLocalPosition(0, 15);
	ScoreDisplayComponent* scoreDisplay = go4.AddComponent<ScoreDisplayComponent>(smallFont);
	scoreComponent->AttachObserver(scoreDisplay);

}

void MakeManuel(vic::Scene* scene, [[maybe_unused]] vic::Minigin* engine, [[maybe_unused]] vic::Font* font, vic::Font* smallFont)
{
	vic::GameObject& go{ scene->CreateGameObject() };
	go.GetTransform().SetLocalPosition(300, 80);

	vic::GameObject& go2{ scene->CreateGameObject() };
	go2.AddComponent<vic::TextRenderComponent>(
		smallFont, "use the WASD to move the first player, use P to to take damage and I&O to get points",
		vic::TextRenderComponent::TextAlignment::left);
	go2.SetParent(&go);

	vic::GameObject& go3{ scene->CreateGameObject() };
	go3.GetTransform().SetLocalPosition(10, 20);
	go3.AddComponent<vic::TextRenderComponent>(
		smallFont, "use the D-Pad to move the second player, use M to to take damage and K&L to get points",
		vic::TextRenderComponent::TextAlignment::left);
	go3.SetParent(&go);

}

void MakeRotatingBalls(vic::Scene* , vic::Minigin* )
{

}

int main(int, char* []) {


	vic::Minigin engine("../Data/Testing/");
	engine.Run(load);


	return 0;
}