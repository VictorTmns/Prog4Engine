#pragma once

#include "BaseComponent.h"
#include "Transform.h"

namespace vic
{
	class PhysicsEngine;
}

namespace vic
{
	class ColliderComponent : public BaseComponent
	{
	public:
		ColliderComponent(GameObject* ownerPtr, const glm::vec2& dimensions, std::function<void(ColliderComponent*, ColliderComponent*)> collisionFunc);
		ColliderComponent(GameObject* ownerPtr, const glm::vec2& dimensions);
		~ColliderComponent() override;

		GameObject* GetOwner() const { return BaseComponent::Owner(); }

	private:
		Transform* m_GOTransformPtr;
		glm::vec2 m_Dimensions;
		std::function<void(ColliderComponent* self, ColliderComponent* other)> m_CollisionFunc;
		bool m_HasOverlapBehavior;

		friend PhysicsEngine;
	};

}
