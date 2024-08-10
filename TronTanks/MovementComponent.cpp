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
	m_CanOverride = true;
}


void MovementComponent::Move(float x, float y)
{
	//BaseComponent::Owner()->GetTransform().AddLocalPosition(
	//	x * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime()) * m_Speed,
	//	y * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime()) * m_Speed);
	//
	//if (m_CanOverride)
	//	m_Velocity = glm::vec2{ x, y };
	//else
	//{
	//	m_Velocity.x += x;
	//	m_Velocity.y += y;
	//}
	m_Velocity.x += x;
	m_Velocity.y += y;

}
