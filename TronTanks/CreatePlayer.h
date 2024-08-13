#pragma once
#include "BarrelComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerLogic.h"
#include "Scene.h"


#include "VelocityMovementComponent.h"
#include "PrimitivesRenderComponent.h"

inline void AddArrowShooting(BarrelComponent* barrelComp, int team)
{
	auto& inputManager = vic::InputManager::GetInstance();

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
}
inline void AddWASDMovement(VelocityMovementComponent* moveComp)
{
	auto& inputManager = vic::InputManager::GetInstance();

	auto moveFunc = [moveComp](float x, float y)
		{
			moveComp->AddVelocity(x, y);
		};

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
inline void AddControllerMovement(VelocityMovementComponent* moveComp, int controllerIdx)
{
	auto& inputManager = vic::InputManager::GetInstance();

	auto moveFunc = [moveComp](float x, float y)
		{
			moveComp->AddVelocity(x, y);
		};

	inputManager.BindToControllerThumbStick(
		moveComp,
		moveFunc,
		controllerIdx,
		false
	);


}
inline void AddControllerShooting(BarrelComponent* barrelComp, int controllerIdx, int team)
{
	auto& inputManager = vic::InputManager::GetInstance();

	inputManager.BindToControllerButton(
		barrelComp,
		[barrelComp, team] { barrelComp->Shoot(BarrelComponent::Direction::right, team); },
		controllerIdx,
		vic::ControllerButton::dpadRight,
		vic::ClickType::pressed
	);


	inputManager.BindToControllerButton(
		barrelComp,
		[barrelComp, team] { barrelComp->Shoot(BarrelComponent::Direction::up, team); },
		controllerIdx,
		vic::ControllerButton::dpadUp,
		vic::ClickType::pressed
	);

	inputManager.BindToControllerButton(
		barrelComp,
		[barrelComp, team] { barrelComp->Shoot(BarrelComponent::Direction::left, team); },
		controllerIdx,
		vic::ControllerButton::dpadLeft,
		vic::ClickType::pressed
	);

	inputManager.BindToControllerButton(
		barrelComp,
		[barrelComp, team] { barrelComp->Shoot(BarrelComponent::Direction::down, team); },
		controllerIdx,
		vic::ControllerButton::dpadDown,
		vic::ClickType::pressed
	);

}

inline vic::GameObject& CreatePlayer(vic::Scene* scene, const glm::vec2& pos, int team, PlayingState* playingState, bool player1)
{
	const glm::vec2 playerDim{ 20.f, 20.f };

	vic::GameObject& player{ scene->CreateGameObject("player") };
	player.GetTransform().SetLocalPosition(pos.x, pos.y);

	//logic
		PlayerLogic* playerLogic = player.AddComponent<PlayerLogic>();
		playerLogic->AttachObserver(playingState);

	//Movement
	VelocityMovementComponent* moveComp = player.AddComponent<VelocityMovementComponent>(500.f);


	if(player1)
	{
		AddWASDMovement(moveComp);
		AddControllerMovement(moveComp, 0);
	}
	else
	{
		AddControllerMovement(moveComp, 1);
	}
	

	//rendering
		player.AddComponent<vic::PrimitivesRenderComponent>(playerDim, SDL_Color{ 255, 0, 0, 0 }, true);

	//collisions
		player.AddComponent<vic::ColliderComponent>(playerDim, moveComp->GetVelocityPointer());

	//overlaps
		std::function<void(vic::OverlapComponent*, vic::OverlapComponent*)> collisionFunc =
		{ [playerLogic, team](vic::OverlapComponent*, vic::OverlapComponent* other) {

			std::string_view otherName{other->Owner()->GetName()};
			if (otherName == "bullet" && !other->Owner()->IsDead())
			{
				if (other->Owner()->GetComponent<BulletLogicComponent>()->GetBulletTeam() != team)
				{
					playerLogic->Hit();
					other->Owner()->Destroy();
				}
			}
		} };

		player.AddComponent<vic::OverlapComponent>(playerDim, collisionFunc);

	//barrel
		vic::GameObject& barrel{ scene->CreateGameObject("barrel") };
		barrel.SetParent(&player);
		barrel.GetTransform().SetLocalPosition(playerDim.x/2, playerDim.y / 2);
		auto barrelComp = barrel.AddComponent<BarrelComponent>();

	if (player1)
	{
		AddArrowShooting(barrelComp, team);
		AddControllerShooting(barrelComp, 1, team);
	}
	else
	{
		AddControllerShooting(barrelComp, 0, team);
	}

	return { player };
}

