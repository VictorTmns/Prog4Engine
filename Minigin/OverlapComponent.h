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

		bool HasOverlapBehaviour() const { return m_HasOverlapBehavior; }
		glm::vec2 GetDimensions() const { return m_Dimensions; }

		void SetOffset(const glm::vec2& offset) { m_Offset = offset; }



		bool Overlaps(const glm::vec2& pos, const glm::vec2& size) const;
		//Also executes it's behaviour if it overlaps
		void OverlapCheck(OverlapComponent& other);

	private:
		Transform* m_GOTransformPtr;
		const glm::vec2 m_Dimensions;
		glm::vec2 m_Offset = { 0.f, 0.f };
		std::function<void(OverlapComponent* self, OverlapComponent* other)> m_CollisionFunc;
		bool m_HasOverlapBehavior;
	};

}
