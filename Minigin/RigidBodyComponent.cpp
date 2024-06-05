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

void RigidBodyComponent::ApplyPhysicsMovement(const glm::vec2& pos, const float rot)
{
	m_GOTranformPtr->SetWorldPosition(pos.x, pos.y);
	m_GOTranformPtr->SetWorldRotation(rot);
}





