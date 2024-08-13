#pragma once
#include <glm/glm.hpp>

#include "CreatePlayer.h"
#include "EnemyLogicComp.h"
#include "EnemyMovementAIComp.h"
#include "EnemyShootingAIComp.h"
#include "InputTypes.h"
#include "VelocityMovementComponent.h"
#include "Scene.h"

void CreateEnemy(vic::Scene* scene, const glm::vec2& pos, bool isRecognizer, PlayingState* playingState)
{
	constexpr glm::vec2 dim{ 20, 20 };

	std::string goName{};
	if (isRecognizer)
		goName = "recognizer";
	else
		goName = "blueTank";


	vic::GameObject& enemy{ scene->CreateGameObject(goName) };
	enemy.GetTransform().SetLocalPosition(pos.x, pos.y);

	//Movement
	VelocityMovementComponent* moveComp {};
	if (!isRecognizer)
		moveComp = enemy.AddComponent<VelocityMovementComponent>(100.f);
	else
		moveComp = enemy.AddComponent<VelocityMovementComponent>(200.f);

	

	//rendering
	enemy.AddComponent<vic::PrimitivesRenderComponent>(dim, SDL_Color{ 0, 0, 255, 0 }, true);



	//barrel
	vic::GameObject& barrel{ scene->CreateGameObject("barrel") };
	barrel.SetParent(&enemy);
	barrel.GetTransform().SetLocalPosition(dim.x/2, dim.y/2);
	auto barrelComp = barrel.AddComponent<BarrelComponent>();

	//AI
	enemy.AddComponent<EnemyMovementAIComp>(moveComp);
	enemy.AddComponent<EnemyShootingAIComp>(barrelComp);
	EnemyLogicComp* enemyLogic = enemy.AddComponent<EnemyLogicComp>();
	enemyLogic->AttachObserver(playingState);

	//collisions
	enemy.AddComponent<vic::ColliderComponent>(dim, moveComp->GetVelocityPointer());

	//overlaps
	std::function<void(vic::OverlapComponent*, vic::OverlapComponent*)> collisionFunc =
	{ [enemyLogic](vic::OverlapComponent*, vic::OverlapComponent* other) {

		std::string_view otherName{other->Owner()->GetName()};
		if (otherName == "bullet")
		{
			if (other->Owner()->GetComponent<BulletLogicComponent>()->GetBulletTeam() != 200)
			{
				enemyLogic->Hit();
				other->Owner()->Destroy();
			}
		}
	} };
	enemy.AddComponent<vic::OverlapComponent>(dim, collisionFunc);

}
