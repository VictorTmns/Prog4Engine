#pragma once
#include "GameObject.h"
#include "PrimitivesRenderComponent.h"

class BarrelComponent : public vic::BaseComponent
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

	void Shoot(Direction direction);

private:
	void ReloadBarrelRenderer();

private:
	Direction m_BarrelDirection;
	vic::PrimitivesRenderComponent* m_BarrelRenderer;
};
