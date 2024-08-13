#pragma once
#include <glm/vec2.hpp>

#include "PrimitivesRenderComponent.h"
#include "Scene.h"

inline void CreateDiamond(vic::Scene* scene, const glm::vec2& pos)
{
	constexpr glm::vec2 dimensions{ 30, 30 };
	vic::GameObject& wall = scene->CreateGameObject("diamond");

	wall.GetTransform().SetWorldPosition(pos.x, pos.y);

	wall.AddComponent<vic::PrimitivesRenderComponent>(dimensions.x / 4, SDL_Color{ 124, 124, 124, 0 })
		->SetOffset(dimensions/2.f);
	wall.AddComponent<vic::OverlapComponent>(dimensions);
}
