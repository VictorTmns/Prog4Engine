#pragma once
#include <memory>

#include "ColliderComponent.h"



namespace vic
{
	class PhysicsEngine final
	{
	public:
		PhysicsEngine() = default;
		~PhysicsEngine() = default;

		void UpdateCollisions();

		void RegisterCollider(ColliderComponent* bodyComponent);
		void UnregisterRigidbodyBox(ColliderComponent* bodyComponent);


		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;

	private:
		std::vector<ColliderComponent*> m_Bodies;

		bool IsOverlapping(const glm::vec2& tr1, const glm::vec2& tr2, const glm::vec2& dim1, const glm::vec2 dim2);
	};
}
