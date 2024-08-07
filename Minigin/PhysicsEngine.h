#pragma once
#include <memory>

#include "RigidBodyComponent.h"



namespace vic
{
	class PhysicsEngine final
	{
	public:
		PhysicsEngine() = default;
		~PhysicsEngine() = default;

		void UpdateCollisions();

		void RegisterRigidBodyBox(RigidBodyComponent* bodyComponent);
		void UnregisterRigidbodyBox(RigidBodyComponent* bodyComponent);


		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;

	private:
		std::vector<RigidBodyComponent*> m_Bodies;

		bool IsOverlapping(const glm::vec2& tr1, const glm::vec2& tr2, const glm::vec2& dim1, const glm::vec2 dim2);
	};
}
