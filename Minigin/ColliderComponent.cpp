#include "ColliderComponent.h"

#include "GameObject.h"
#include "Scene.h"

using namespace vic;


ColliderComponent::ColliderComponent(GameObject* ownerPtr, const glm::vec2& dimensions, glm::vec2* velocityPointer)
	: BaseComponent{ ownerPtr }
	, m_GOTransformPtr{ &ownerPtr->GetTransform() }
	, m_Dimensions{ dimensions }
	, m_VelocityPtr{ velocityPointer }
	, m_staticObject{ false }
{
	ownerPtr->GetScene()->GetPhysicsEngine().RegisterColliderComp(this);
}
ColliderComponent::ColliderComponent(GameObject* ownerPtr, const glm::vec2& dimensions)
	: BaseComponent{ ownerPtr }
	, m_GOTransformPtr{ &ownerPtr->GetTransform() }
	, m_Dimensions{ dimensions }
	, m_VelocityPtr{ nullptr}
	, m_staticObject{ true }
{
	ownerPtr->GetScene()->GetPhysicsEngine().RegisterColliderComp(this);
}

ColliderComponent::~ColliderComponent()
{
	Owner()->GetScene()->GetPhysicsEngine().UnregisterColliderComp(this);
}
