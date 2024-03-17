#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "GameActorComponent.h"
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
	auto& scene = minigin::SceneManager::GetInstance().CreateScene("Demo");
	auto& inputManager = minigin::InputManager::GetInstance();
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
	texture = go->AddComponent<minigin::TextureRenderComponent>();
	texture->SetTexture("yellowDot.png");
	minigin::BaseComponent* actorComponent = go->AddComponent<GameActorComponent>();

	auto f = std::function<void(minigin::BaseComponent* actor)>(&GameActorComponent::MoveUp);
	inputManager.BindToKeyboard(
		actorComponent, f,
		SDLK_UP, minigin::ClickType::hold);
	
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