#pragma once
#include "BulletLogicComponent.h"
#include "GameObject.h"
#include "PrimitivesRenderComponent.h"
#include "Scene.h"

inline vic::GameObject* CreateBullet(vic::Scene* scene, const glm::vec2& startPos, const glm::vec2& startDir)
{
	vic::GameObject& bullet = scene->CreateGameObject("bullet");
	bullet.AddComponent<BulletLogicComponent>(startDir);
	bullet.AddComponent<vic::PrimitivesRenderComponent>(2.f, SDL_Color{ 0, 0, 255, 0 });
	bullet.GetTransform().SetWorldPosition(startPos.x, startPos.y);

	//bullet.AddComponent<vic::ColliderComponent>( )

	return &bullet;
}