#pragma once
#include "BulletLogicComponent.h"
#include "GameObject.h"
#include "PrimitivesRenderComponent.h"
#include "Scene.h"

inline vic::GameObject* CreateBullet(vic::Scene* scene, const glm::vec2& startPos, const glm::vec2& startDir, int team)
{
	const float bulletSize{ 3.f };
	const glm::vec2 bulletLeftBottom{ startPos.x - bulletSize / 2.f, startPos.y - bulletSize / 2.f };

	vic::GameObject& bullet = scene->CreateGameObject("bullet");
	bullet.AddComponent<BulletLogicComponent>(startDir, team);
	bullet.AddComponent<vic::PrimitivesRenderComponent>(bulletSize, SDL_Color{ 0, 0, 255, 0 });
	bullet.GetTransform().SetWorldPosition(bulletLeftBottom.x, bulletLeftBottom.y);


	std::function<void(vic::OverlapComponent*, vic::OverlapComponent*)> collisionFunc =
	{ [](vic::OverlapComponent* self, vic::OverlapComponent* other){

		std::string_view otherName{other->GetOwner()->GetName()};
		if (otherName == "wall")
		{
			BulletLogicComponent* logicSelf = self->GetOwner()->GetComponent<BulletLogicComponent>();
			logicSelf->BounceOutWall();
		}
	}};

	bullet.AddComponent<vic::OverlapComponent>(glm::vec2{ bulletSize, bulletSize }, collisionFunc);

	return &bullet;
}