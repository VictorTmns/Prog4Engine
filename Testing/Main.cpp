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
void MakeRotatingBalls(minigin::Scene* scene, minigin::Minigin* engine);

void load(minigin::Minigin* engine)
{
	[[maybe_unused]] auto& inputManager = minigin::InputManager::GetInstance();
	auto scene = minigin::SceneManager::GetInstance().CreateScene("Demo");
	auto font = minigin::ResourceManager::GetInstance().GetFont("Lingua.otf", 36);
	auto smallFont = minigin::ResourceManager::GetInstance().GetFont("Lingua.otf", 15);
	std::function func = [](const minigin::BaseComponent* subject)
		{
			return (dynamic_cast<const ScoreComponent*>(subject)->GetScore() >= 500);
		};


	// FPS GAME OBJECT
	minigin::GameObject& go = scene->CreateGameObject();
	go.AddComponent<minigin::FPSComponent>(font);
	go.SetLocalTranslate(20.f, 430.f);

	// DAE LOGO
	minigin::GameObject& go2 = scene->CreateGameObject();
	auto texture = go2.AddComponent<minigin::TextureRenderComponent>();
	texture->SetTexture("logo.tga");
	go2.SetLocalTranslate(216, 180);

	// TEXT
	minigin::GameObject& go3 = scene->CreateGameObject();
	go3.AddComponent<minigin::TextRenderComponent>(font, "Programming 4 Assignment");
	go3.SetLocalTranslate(80, 20);


	MakePlayer1(scene, engine, font, smallFont);
	MakePlayer2(scene, engine, font, smallFont);
	MakeManuel(scene, engine, font, smallFont);

	MakeRotatingBalls(scene, engine);
}

void MakePlayer1(minigin::Scene* scene, minigin::Minigin* ,  minigin::Font*, minigin::Font* smallFont)
{
	auto& inputManager = minigin::InputManager::GetInstance();

	//PLAYER CHARACTER
	minigin::GameObject& go{scene->CreateGameObject()};
	go.SetLocalTranslate(100, 230);

	go.AddComponent<CircleRenderComponent>(10.f, SDL_Color{ 255, 255, 0, 255 });


	KeyboardTestComponent* actorComponent = go.AddComponent<KeyboardTestComponent>();
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>([actorComponent] { actorComponent->Move(-1.f, 0.f); }),
		SDLK_a,
		minigin::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>([actorComponent] { actorComponent->Move(0.f, 1.f); }),
		SDLK_s,
		minigin::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>([actorComponent] { actorComponent->Move(0.f, -1.f); }),
		SDLK_w,
		minigin::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		[actorComponent] { actorComponent->Move(1.f, 0.f); },
		SDLK_d,
		minigin::ClickType::hold);



	minigin::LivesComponent* livesComponent = go.AddComponent<minigin::LivesComponent>(3);
	inputManager.BindToKeyboard(livesComponent,
	                            [livesComponent] { livesComponent->TakeDamage(); },
		SDLK_p,
		minigin::ClickType::pressed);


	ScoreComponent* scoreComponent = go.AddComponent<ScoreComponent>();

	ScoreTestComponent* scoreTestComponent = go.AddComponent<ScoreTestComponent>(scoreComponent);
	inputManager.BindToKeyboard(scoreTestComponent,
	                            [scoreTestComponent] { scoreTestComponent->PickUpItem(); },
								SDLK_o,
								minigin::ClickType::pressed);
	inputManager.BindToKeyboard(scoreTestComponent,
	                            [scoreTestComponent] { scoreTestComponent->KillEnemy(); },
		SDLK_i,
		minigin::ClickType::pressed);

	// SOUND COMPONENT
	PlaySoundComponent* playSoundComponent = go.AddComponent<PlaySoundComponent>();
	inputManager.BindToKeyboard(playSoundComponent,
	                            [playSoundComponent] { playSoundComponent->PlaySound(); },
								SDLK_t,
								minigin::ClickType::pressed);




	minigin::GameObject& go2 = scene->CreateGameObject();
	go.SetLocalTranslate(0, 200);


	// LIVES DISPLAY 1
	minigin::GameObject& go3 = scene->CreateGameObject();
	go3.SetParent(&go2, false);
	minigin::LivesDisplayComponent* livesDisplay = go3.AddComponent<minigin::LivesDisplayComponent>(smallFont);
	livesComponent->AttachObserver(livesDisplay);


	// SCORE DISPLAY 1
	minigin::GameObject& go4 = scene->CreateGameObject();
	go4.SetParent(&go2, false);
	go4.SetLocalTranslate(0, 15);
	minigin::ScoreDisplayComponent* scoreDisplay = go4.AddComponent<minigin::ScoreDisplayComponent>(smallFont);
	scoreComponent->AttachObserver(scoreDisplay);

	


}

void MakePlayer2(minigin::Scene* scene, minigin::Minigin*, minigin::Font* , minigin::Font* smallFont)
{
	auto& inputManager = minigin::InputManager::GetInstance();

	// PLAYER CHARACTER 2
	minigin::GameObject& go{ scene->CreateGameObject() };
	go.SetLocalTranslate(80, 300);

	go.AddComponent<CircleRenderComponent>(10.f, SDL_Color{ 255, 255, 0, 255 });

	KeyboardTestComponent* newComponent = go.AddComponent<KeyboardTestComponent>();
	inputManager.BindToControllerThumbStick(
		newComponent,
		std::bind_front(&KeyboardTestComponent::Move, newComponent),
		0,
		true);



	minigin::LivesComponent* livesComponent = go.AddComponent<minigin::LivesComponent>(3);
	inputManager.BindToKeyboard(livesComponent,
	                            [livesComponent] { livesComponent->TakeDamage(); },
		SDLK_m,
		minigin::ClickType::pressed);


	ScoreComponent* scoreComponent = go.AddComponent<ScoreComponent>();

	ScoreTestComponent* scoreTestComponent = go.AddComponent<ScoreTestComponent>(scoreComponent);
	inputManager.BindToKeyboard(scoreTestComponent,
	                            [scoreTestComponent] { scoreTestComponent->PickUpItem(); },
		SDLK_k,
		minigin::ClickType::pressed);
	inputManager.BindToKeyboard(scoreTestComponent,
	                            [scoreTestComponent] { scoreTestComponent->KillEnemy(); },
		SDLK_l,
		minigin::ClickType::pressed);



	minigin::GameObject& go2{ scene->CreateGameObject() };
	go.SetLocalTranslate(0, 240);


	// LIVES DISPLAY 2
	minigin::GameObject& go3{ scene->CreateGameObject() };
	go3.SetParent(&go2, false);
	minigin::LivesDisplayComponent* livesDisplay = go3.AddComponent<minigin::LivesDisplayComponent>(smallFont);
	livesComponent->AttachObserver(livesDisplay);


	// SCORE DISPLAY 2
	minigin::GameObject& go4{ scene->CreateGameObject() };
	go4.SetParent(&go2, false);
	go4.SetLocalTranslate(0, 15);
	minigin::ScoreDisplayComponent* scoreDisplay = go4.AddComponent<minigin::ScoreDisplayComponent>(smallFont);
	scoreComponent->AttachObserver(scoreDisplay);

}

void MakeManuel(minigin::Scene* scene, [[maybe_unused]] minigin::Minigin* engine, [[maybe_unused]] minigin::Font* font, minigin::Font* smallFont)
{
	minigin::GameObject& go{ scene->CreateGameObject() };
	go.SetLocalTranslate(300, 80);

	minigin::GameObject& go2{ scene->CreateGameObject() };
	go2.AddComponent<minigin::TextRenderComponent>(
		smallFont, "use the WASD to move the first player, use P to to take damage and I&O to get points",
		minigin::TextRenderComponent::TextAlignment::left);
	go2.SetParent(&go);

	minigin::GameObject& go3{ scene->CreateGameObject() };
	go3.SetLocalTranslate(10, 20);
	go3.AddComponent<minigin::TextRenderComponent>(
		smallFont, "use the D-Pad to move the second player, use M to to take damage and K&L to get points",
		minigin::TextRenderComponent::TextAlignment::left);
	go3.SetParent(&go);

}

void MakeRotatingBalls(minigin::Scene* , minigin::Minigin* )
{

}

int main(int, char* []) {


	minigin::Minigin engine("../Data/Testing/");
	engine.Run(load);


	return 0;
}