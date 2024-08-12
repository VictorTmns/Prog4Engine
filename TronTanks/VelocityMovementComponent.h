#pragma once

#include <glm/vec2.hpp>

#include "BaseComponent.h"


class VelocityMovementComponent final : public vic::BaseComponent
{
public:
	VelocityMovementComponent(vic::GameObject* ownerPtr, float speed);

	void Update() override;
	void SetVelocity(float x, float y);
	glm::vec2* GetVelocityPointer() { return &m_ToMove; }

	void AddVelocity(float x, float y);
private:
	float m_Speed;
	glm::vec2 m_ToMove;
	bool m_ResetVelocity;

	
};
