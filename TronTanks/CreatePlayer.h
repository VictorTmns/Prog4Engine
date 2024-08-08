#pragma once
#include "BarrelComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Scene.h"


#include "MovementComponent.h"
#include "PrimitivesRenderComponent.h"


inline void AddWASDMovement(vic::BaseComponent* moveComp, std::function<void(float, float)> moveFunc)
{
	auto& inputManager = vic::InputManager::GetInstance();

	inputManager.BindToKeyboard(
		moveComp,
		[moveFunc] { moveFunc(-1.f, 0.f); },
		SDLK_a,
		vic::ClickType::hold);
	inputManager.BindToKeyboard(
		moveComp,
		[moveFunc] { moveFunc(0.f, 1.f); },
		SDLK_s,
		vic::ClickType::hold);
	inputManager.BindToKeyboard(
		moveComp,
		[moveFunc] { moveFunc(0.f, -1.f); },
		SDLK_w,
		vic::ClickType::hold);
	inputManager.BindToKeyboard(
		moveComp,
		[moveFunc] { moveFunc(1.f, 0.f); },
		SDLK_d,
		vic::ClickType::hold);
}
inline vic::GameObject& BuildPlayer()
{
	vic::Scene* scene = vic::SceneManager::GetInstance().GetScene("main");
	auto& inputManager = vic::InputManager::GetInstance();


	vic::GameObject& player{ scene->CreateGameObject("player") };
	player.GetTransform().SetLocalPosition(50, 50);

	//Movement
		MovementComponent* moveComp = player.AddComponent<MovementComponent>(50.f);
		AddWASDMovement(moveComp, [moveComp](auto&& PH1, auto&& PH2)
		{
			moveComp->Move(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
		});

	//rendering
		player.AddComponent<vic::PrimitivesRenderComponent>(glm::vec2{40, 40}, SDL_Color{ 255, 0, 0, 0 }, true);

	//barrel
		vic::GameObject& barrel{ scene->CreateGameObject("barrel") };
		barrel.SetParent(&player);
		barrel.GetTransform().SetLocalPosition(20, 20);
		auto barrelComp = barrel.AddComponent<BarrelComponent>();

		inputManager.BindToKeyboard(
			barrelComp,
			[barrelComp] {barrelComp->Shoot(BarrelComponent::Direction::left); },
			SDLK_LEFT,
			vic::ClickType::pressed
		);
		inputManager.BindToKeyboard(
			barrelComp,
			[barrelComp] {barrelComp->Shoot(BarrelComponent::Direction::up); },
			SDLK_UP,
			vic::ClickType::pressed
		);
		inputManager.BindToKeyboard(
			barrelComp,
			[barrelComp] {barrelComp->Shoot(BarrelComponent::Direction::right); },
			SDLK_RIGHT,
			vic::ClickType::pressed
		);
		inputManager.BindToKeyboard(
			barrelComp,
			[barrelComp] {barrelComp->Shoot(BarrelComponent::Direction::down); },
			SDLK_DOWN,
			vic::ClickType::pressed
		);

	return { player };
}

