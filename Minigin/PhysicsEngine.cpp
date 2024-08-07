#include "PhysicsEngine.h"

#include <stdexcept>

#include "RigidBodyComponent.h"




using namespace vic;

void PhysicsEngine::UpdateCollisions()
{
	for (RigidBodyComponent* body : m_Bodies)
	{
		if(!body->m_HasOverlapBehavior)
			continue;

		for (RigidBodyComponent* body2 : m_Bodies)
		{
			if(body == body2)
				continue;


			if (!IsOverlapping(body->m_GOTransformPtr->Position(), body2->m_GOTransformPtr->Position(), body->m_Dimensions, body2->m_Dimensions))
				continue;


			body->m_CollisionFunc(body, body2);
		}
	}
}

void PhysicsEngine::RegisterRigidBodyBox(RigidBodyComponent* bodyComponent)
{
	m_Bodies.push_back(bodyComponent);
}

void PhysicsEngine::UnregisterRigidbodyBox(RigidBodyComponent* bodyComponent)
{
	auto bodyIt = std::ranges::find(m_Bodies, bodyComponent);

	if (bodyIt == m_Bodies.end())
		throw std::runtime_error("unregistering unknown collider");

	m_Bodies.erase(bodyIt);
}

bool PhysicsEngine::IsOverlapping(const glm::vec2& tr1, const glm::vec2& tr2, const glm::vec2& dim1,
	const glm::vec2 dim2)
{
	return (
		   tr1.x			< (tr2.x + dim2.x)
		&& (tr1.x + dim1.x) > tr2.x
		&& (tr1.y + dim1.y) > tr2.y
		&& tr1.y			< (tr2.y + dim2.y)
		);

}
