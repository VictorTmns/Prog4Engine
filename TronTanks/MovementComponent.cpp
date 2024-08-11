#include "MovementComponent.h"

#include "GameObject.h"
#include <GameTime.h>

#include "InputManager.h"

MovementComponent::MovementComponent(vic::GameObject* ownerPtr, float speed)
	: BaseComponent{ ownerPtr }
	, m_Speed{speed}
{
}

void MovementComponent::Update()
{
	if (m_ResetVelocity == true)
		m_Velocity = glm::vec2{ 0.f, 0.f };
	m_ResetVelocity = true;
}


void MovementComponent::Move(float x, float y)
{
	if (m_ResetVelocity)
	{
		m_Velocity = glm::vec2{x * m_Speed, y * m_Speed};
		m_ResetVelocity = false;
	}
	else
	{
		m_Velocity.x += x * m_Speed;
		m_Velocity.y += y * m_Speed;
	}
}
