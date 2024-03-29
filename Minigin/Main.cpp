#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "CircleRenderComponent.h"
#include "FPSComponent.h"
#include "KeyboardTestComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Minigin.h"
#include "OrbitComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextRenderComponent.h"
#include "Scene.h"
#include "TextureRenderComponent.h"
#include "ThrashTheCacheComponent.h"

void load()
{
	auto& inputManager = minigin::InputManager::GetInstance();
	auto& scene = minigin::SceneManager::GetInstance().CreateScene("Demo");
	auto font = minigin::ResourceManager::GetInstance().GetFont("Lingua.otf", 36);


	auto go = std::make_unique<minigin::GameObject>();
	go->AddComponent<minigin::FPSComponent>(font);
	go->SetLocalTranslate(20.f, 430.f);
	scene.AddGameObject(std::move(go));

	go.reset();
	go = std::make_unique<minigin::GameObject>();
	auto texture = go->AddComponent<minigin::TextureRenderComponent>();
	texture->SetTexture("logo.tga");
	go->SetLocalTranslate(216, 180);

	scene.AddGameObject(std::move(go));



	go.reset();
	go = std::make_unique<minigin::GameObject>();
	go->AddComponent<minigin::TextRenderComponent>(font, "Programming 4 Assignment");
	go->SetLocalTranslate(80, 20);
	scene.AddGameObject(std::move(go));

	//go.reset();
	//go = std::make_unique<minigin::GameObject>();
	//go->AddComponent<ThrashTheCacheComponent>();
	//scene.AddGameObject(std::move(go));

	go.reset();
	go = std::make_unique<minigin::GameObject>();
	go->SetLocalTranslate(100, 300);

	go->AddComponent<CircleRenderComponent>(10.f, SDL_Color{255, 255, 0, 255});



	KeyboardTestComponent* actorComponent = go->AddComponent<KeyboardTestComponent>();
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>(std::bind(&KeyboardTestComponent::MoveUp, actorComponent)),
		SDLK_w,
		minigin::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>(std::bind(&KeyboardTestComponent::MoveRight, actorComponent)),
		SDLK_d,
		minigin::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>(std::bind(&KeyboardTestComponent::MoveLeft, actorComponent)),
		SDLK_a,
		minigin::ClickType::hold);
	inputManager.BindToKeyboard(
		actorComponent,
		std::function<void()>(std::bind(&KeyboardTestComponent::MoveDown, actorComponent)),
		SDLK_s,
		minigin::ClickType::hold);

	scene.AddGameObject(std::move(go));





	go.reset();
	go = std::make_unique<minigin::GameObject>();
	go->SetLocalTranslate(80, 300);

	go->AddComponent<CircleRenderComponent>(10.f, SDL_Color{255, 255, 0, 255});


	KeyboardTestComponent* newComponent = go->AddComponent<KeyboardTestComponent>();
	inputManager.BindToControllerThumbStick(
		newComponent,
		std::function<void(float x, float y)>(std::bind_front(&KeyboardTestComponent::Move, newComponent)),
		0,
		true);


	scene.AddGameObject(std::move(go));

	
	//auto go2 = new minigin::GameObject(sceneRoot);
	//go2->SetLocalTranslate(10, 0);
	//
	//texture = go2->AddComponent<minigin::TextureRenderComponent>();
	//texture->SetTexture("yellowDot.png");

	//auto rotatingComponent = go2->AddComponent< minigin::OrbitComponent>(0.5f);;
}

int main(int, char*[]) {
	minigin::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}