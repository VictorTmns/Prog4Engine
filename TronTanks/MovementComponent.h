#pragma once

#include <glm/vec2.hpp>

#include "BaseComponent.h"


class MovementComponent final : public vic::BaseComponent
{
public:
	MovementComponent(vic::GameObject* ownerPtr, float speed);

	void Update() override;
	glm::vec2* GetVelocityPointer() { return &m_Velocity; }

	void Move(float x, float y);
private:
	float m_Speed;
	glm::vec2 m_Velocity;
	bool m_CanOverride;
};
