#pragma once

#include "BaseComponent.h"
#include "Transform.h"

namespace vic
{
	class PhysicsEngine;
}

namespace vic
{
	class RigidBodyComponent : public BaseComponent
	{
	public:
		RigidBodyComponent(GameObject* ownerPtr, const glm::vec2& dimensions, std::function<void(RigidBodyComponent*, RigidBodyComponent*)> collisionFunc);
		RigidBodyComponent(GameObject* ownerPtr, const glm::vec2& dimensions);
		~RigidBodyComponent() override;

		GameObject* GetOwner() const { return BaseComponent::Owner(); }

	private:
		Transform* m_GOTransformPtr;
		glm::vec2 m_Dimensions;
		std::function<void(RigidBodyComponent* self, RigidBodyComponent* other)> m_CollisionFunc;
		bool m_HasOverlapBehavior;

		friend PhysicsEngine;
	};

}
