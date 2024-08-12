#include "VelocityMovementComponent.h"

#include "GameObject.h"
#include <GameTime.h>

#include "InputManager.h"

VelocityMovementComponent::VelocityMovementComponent(vic::GameObject* ownerPtr, float speed)
	: BaseComponent{ownerPtr}
	  , m_Speed{speed}, m_ToMove{}, m_ResetVelocity{false}
{
}

void VelocityMovementComponent::Update()
{
	if (m_ResetVelocity == true)
		m_ToMove = glm::vec2{ 0.f, 0.f };
	m_ResetVelocity = true;
}


void VelocityMovementComponent::SetVelocity(float x, float y)
{
	m_ToMove.x = x * m_Speed;
	m_ToMove.y = y * m_Speed;
}

void VelocityMovementComponent::AddVelocity(float x, float y)
{
	if (m_ResetVelocity)
	{
		m_ToMove = glm::vec2{x * m_Speed, y * m_Speed};
		m_ResetVelocity = false;
	}
	else
	{
		m_ToMove.x += x * m_Speed;
		m_ToMove.y += y * m_Speed;
	}
}
