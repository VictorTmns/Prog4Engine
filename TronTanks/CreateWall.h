#pragma once
#include "GameObject.h"
#include "PrimitivesRenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"


vic::GameObject* CreateWall(vic::Scene* scene, const glm::vec2& pos)
{
	vic::GameObject& wall = scene->CreateGameObject("wall");

	constexpr glm::vec2 dimensions{ 30, 30 };

	wall.AddComponent<vic::PrimitivesRenderComponent>(dimensions, SDL_Color{ 255, 255, 255, 0 });

	wall.AddComponent<vic::ColliderComponent>(dimensions);

}