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
	assert(m_GOTransformPtr != nullptr);
	ownerPtr->GetScene()->GetPhysicsEngine().RegisterOverlapComp(this);
}

OverlapComponent::OverlapComponent(GameObject* ownerPtr, const glm::vec2& dimensions)
	: BaseComponent{ ownerPtr }
	, m_GOTransformPtr{ &ownerPtr->GetTransform() }
	, m_Dimensions{ dimensions }
	, m_CollisionFunc{  }
	, m_HasOverlapBehavior{ false }
{
	assert(m_GOTransformPtr != nullptr);
	ownerPtr->GetScene()->GetPhysicsEngine().RegisterOverlapComp(this);
}

OverlapComponent::~OverlapComponent()
{
	BaseComponent::Owner()->GetScene()->GetPhysicsEngine().UnregisterOverlapComp(this);
}

bool OverlapComponent::Overlaps(const glm::vec2& pos, const glm::vec2& size) const
{
	return PhysicsEngine::RectVsRect(pos, size, m_GOTransformPtr->Position(), m_Dimensions);
}

void OverlapComponent::OverlapCheck(OverlapComponent& other)
{
	if( PhysicsEngine::RectVsRect(other.m_GOTransformPtr->Position(), other.m_Dimensions, m_GOTransformPtr->Position(), m_Dimensions))
		m_CollisionFunc(this, &other);
}
