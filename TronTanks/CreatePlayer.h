#pragma once
#include "BarrelComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerLogic.h"
#include "Scene.h"


#include "VelocityMovementComponent.h"
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
inline vic::GameObject& CreatePlayer(vic::Scene* scene, const glm::vec2& pos, int team)
{
	auto& inputManager = vic::InputManager::GetInstance();

	const glm::vec2 playerDim{ 20.f, 20.f };

	vic::GameObject& player{ scene->CreateGameObject("player") };
	player.GetTransform().SetLocalPosition(pos.x, pos.y);

	//logic
		PlayerLogic* playerLogic = player.AddComponent<PlayerLogic>();

	//Movement
		VelocityMovementComponent* moveComp = player.AddComponent<VelocityMovementComponent>(500.f);
		AddWASDMovement(moveComp, [moveComp](auto&& PH1, auto&& PH2)
		{
			moveComp->AddVelocity(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
		});

	//rendering
		player.AddComponent<vic::PrimitivesRenderComponent>(playerDim, SDL_Color{ 255, 0, 0, 0 }, true);

	//collisions
		player.AddComponent<vic::ColliderComponent>(playerDim, moveComp->GetVelocityPointer());

	//overlaps
		std::function<void(vic::OverlapComponent*, vic::OverlapComponent*)> collisionFunc =
		{ [playerLogic, team](vic::OverlapComponent*, vic::OverlapComponent* other) {

			std::string_view otherName{other->Owner()->GetName()};
			if (otherName == "bullet")
			{
				if (other->Owner()->GetComponent<BulletLogicComponent>()->GetBulletTeam() != team)
				{
					playerLogic->Hit();
					other->Owner()->Destroy();
				}
			}
		} };

		player.AddComponent<vic::OverlapComponent>(playerDim);

	//barrel
		vic::GameObject& barrel{ scene->CreateGameObject("barrel") };
		barrel.SetParent(&player);
		barrel.GetTransform().SetLocalPosition(playerDim.x/2, playerDim.y / 2);
		auto barrelComp = barrel.AddComponent<BarrelComponent>();

		inputManager.BindToKeyboard(
			barrelComp,
			[barrelComp, team] {barrelComp->Shoot(BarrelComponent::Direction::left, team); },
			SDLK_LEFT,
			vic::ClickType::pressed
		);
		inputManager.BindToKeyboard(
			barrelComp,
			[barrelComp, team] {barrelComp->Shoot(BarrelComponent::Direction::up, team); },
			SDLK_UP,
			vic::ClickType::pressed
		);
		inputManager.BindToKeyboard(
			barrelComp,
			[barrelComp, team] {barrelComp->Shoot(BarrelComponent::Direction::right, team); },
			SDLK_RIGHT,
			vic::ClickType::pressed
		);
		inputManager.BindToKeyboard(
			barrelComp,
			[barrelComp, team] {barrelComp->Shoot(BarrelComponent::Direction::down, team); },
			SDLK_DOWN,
			vic::ClickType::pressed
		);

	return { player };
}

