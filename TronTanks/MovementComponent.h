#pragma once

#include "BaseComponent.h"

class MovementComponent final : public vic::BaseComponent
{
public:
	MovementComponent(vic::GameObject* ownerPtr, float speed);


	void Move(float x, float y);
private:
	float m_Speed;

};
