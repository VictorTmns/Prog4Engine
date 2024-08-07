#include "RigidBodyComponent.h"

#include <utility>

#include "GameObject.h"
#include "Scene.h"

using namespace vic;

RigidBodyComponent::RigidBodyComponent(GameObject* ownerPtr, const glm::vec2& dimensions, std::function<void(RigidBodyComponent*, RigidBodyComponent*)> collisionFunc)
	: BaseComponent{ownerPtr}
	, m_GOTransformPtr{&ownerPtr->GetTransform()}
	, m_Dimensions{dimensions}
	, m_CollisionFunc{std::move(collisionFunc)}
	, m_HasOverlapBehavior{ true }
{
	ownerPtr->GetScene()->GetPhysicsEngine().RegisterRigidBodyBox(this);
}

RigidBodyComponent::RigidBodyComponent(GameObject* ownerPtr, const glm::vec2& dimensions)
	: BaseComponent{ ownerPtr }
	, m_GOTransformPtr{ &ownerPtr->GetTransform() }
	, m_Dimensions{ dimensions }
	, m_CollisionFunc{  }
	, m_HasOverlapBehavior{ false }
{
	ownerPtr->GetScene()->GetPhysicsEngine().RegisterRigidBodyBox(this);
}

RigidBodyComponent::~RigidBodyComponent()
{
	BaseComponent::Owner()->GetScene()->GetPhysicsEngine().UnregisterRigidbodyBox(this);
}
