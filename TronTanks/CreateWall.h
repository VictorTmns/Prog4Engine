#pragma once
#include "GameObject.h"
#include "PrimitivesRenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"


vic::GameObject* CreateWall(vic::Scene* scene, const glm::vec2& pos)
{
	constexpr glm::vec2 dimensions{ 30, 30 };
	vic::GameObject& wall = scene->CreateGameObject("wall");

	wall.GetTransform().SetWorldPosition(pos.x, pos.y);

	wall.AddComponent<vic::PrimitivesRenderComponent>(dimensions, SDL_Color{ 255, 255, 255, 0 });
	wall.AddComponent<vic::ColliderComponent>(dimensions);
	wall.AddComponent<vic::OverlapComponent>(dimensions);

	return &wall;
}