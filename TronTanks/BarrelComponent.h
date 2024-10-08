﻿#pragma once
#include "BulletLogicComponent.h"
#include "GameObject.h"
#include "PrimitivesRenderComponent.h"

class BarrelComponent final : public vic::BaseComponent
{
public:
	enum class Direction
	{
		up,
		down,
		left,
		right
	};

	BarrelComponent(vic::GameObject* ownerPtr);

	void Shoot(Direction direction, int team);

private:
	void ReloadBarrelRenderer();
	static glm::vec2 DirectionToVec(Direction dir);
private:
	Direction m_BarrelDirection;
	vic::PrimitivesRenderComponent* m_BarrelRenderer;
};
