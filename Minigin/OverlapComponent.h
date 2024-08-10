#pragma once

#include "BaseComponent.h"
#include "Transform.h"

namespace vic
{
	class PhysicsEngine;
}

namespace vic
{
	class OverlapComponent : public BaseComponent
	{
	public:
		OverlapComponent(GameObject* ownerPtr, const glm::vec2& dimensions, std::function<void(OverlapComponent*, OverlapComponent*)> collisionFunc);
		OverlapComponent(GameObject* ownerPtr, const glm::vec2& dimensions);
		~OverlapComponent() override;

		GameObject* GetOwner() const { return BaseComponent::Owner(); }
		void SetOffset(const glm::vec2& offset) { m_Offset = offset; }

	private:
		Transform* m_GOTransformPtr;
		glm::vec2 m_Dimensions;
		glm::vec2 m_Offset = { 0.f, 0.f };
		std::function<void(OverlapComponent* self, OverlapComponent* other)> m_CollisionFunc;
		bool m_HasOverlapBehavior;

		friend PhysicsEngine;
	};

}
