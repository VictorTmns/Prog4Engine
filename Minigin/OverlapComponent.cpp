#include "OverlapComponent.h"

#include <utility>

#include "GameObject.h"
#include "Scene.h"

using namespace vic;

OverlapComponent::OverlapComponent(GameObject* ownerPtr, const glm::vec2& dimensions, std::function<void(OverlapComponent*, OverlapComponent*)> collisionFunc)
	: BaseComponent{ownerPtr}
	, m_GOTransformPtr{&ownerPtr->GetTransform()}
	, m_Dimensions{dimensions}
	, m_CollisionFunc{std::move(collisionFunc)}
	, m_HasOverlapBehavior{ true }
{
	ownerPtr->GetScene()->GetPhysicsEngine().RegisterOverlapComp(this);
}

OverlapComponent::OverlapComponent(GameObject* ownerPtr, const glm::vec2& dimensions)
	: BaseComponent{ ownerPtr }
	, m_GOTransformPtr{ &ownerPtr->GetTransform() }
	, m_Dimensions{ dimensions }
	, m_CollisionFunc{  }
	, m_HasOverlapBehavior{ false }
{
	ownerPtr->GetScene()->GetPhysicsEngine().RegisterOverlapComp(this);
}

OverlapComponent::~OverlapComponent()
{
	BaseComponent::Owner()->GetScene()->GetPhysicsEngine().UnregisterOverlapComp(this);
}
