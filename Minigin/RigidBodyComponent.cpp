#include "RigidBodyComponent.h"

#include "GameObject.h"
#include "Scene.h"

using namespace vic;

RigidBodyComponent::RigidBodyComponent(GameObject* ownerPtr, const glm::vec2& boxSize, const BodySettings& settings,
	const PhysicsSettings& pSettings)
	: BaseComponent{ownerPtr}
	, m_GOTranformPtr{&(ownerPtr->GetTransform())}
{
	Owner()->GetScene()->GetPhysicsEngine().RegisterRigidBodyBox(this, m_GOTranformPtr, boxSize, settings, pSettings);
}

RigidBodyComponent::~RigidBodyComponent()
{
	Owner()->GetScene()->GetPhysicsEngine().DestroyComponent(this);
}

void RigidBodyComponent::ApplyForceToCenter(const glm::vec2& force)
{
	Owner()->GetScene()->GetPhysicsEngine().ApplyForceToCenter(this, force);
}

void RigidBodyComponent::ApplyForceToPoint(const glm::vec2& force, const glm::vec2& point)
{
	Owner()->GetScene()->GetPhysicsEngine().ApplyForceToPoint(this, force, point);
}

void RigidBodyComponent::ApplyTorque(float torque)
{
	Owner()->GetScene()->GetPhysicsEngine().ApplyTorque(this, torque);
}

glm::vec2 RigidBodyComponent::GetVelocity()
{
	return Owner()->GetScene()->GetPhysicsEngine().GetVelocity(this);
}

float vic::RigidBodyComponent::GetAngularVelocity()
{
	return Owner()->GetScene()->GetPhysicsEngine().GetAngularVelocity(this);
}

float vic::RigidBodyComponent::GetGravityScale()
{
	return Owner()->GetScene()->GetPhysicsEngine().GetGravityScale(this);
}

float vic::RigidBodyComponent::GetInertia()
{
	return Owner()->GetScene()->GetPhysicsEngine().GetInertia(this);
}

void RigidBodyComponent::ApplyPhysicsMovementCallback(const glm::vec2& pos, const float rot)
{
	m_GOTranformPtr->SetWorldPosition(pos.x, pos.y);
	m_GOTranformPtr->SetWorldRotation(rot);
}





