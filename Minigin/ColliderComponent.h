#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "Transform.h"

namespace vic
{
	class PhysicsEngine;


	class ColliderComponent final : public BaseComponent
	{
	public:
		ColliderComponent(GameObject* ownerPtr, const glm::vec2& dimensions, glm::vec2* velocityPtr);
		ColliderComponent(GameObject* ownerPtr, const glm::vec2& dimensions);
		~ColliderComponent() override;
	
		void ChangeVelocityPtr(glm::vec2* newVelocityPointer) { m_VelocityPtr = newVelocityPointer; }
	
	private:
		const bool m_staticObject;
		Transform* m_GOTransformPtr;
		glm::vec2 m_Dimensions;
		glm::vec2* m_VelocityPtr;
	
		friend PhysicsEngine;
	};
}