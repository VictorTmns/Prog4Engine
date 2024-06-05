#pragma once
#include <memory>

#include "RigidBodyComponent.h"



namespace vic
{
	class PhysicsEngine final
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();

		void UpdatePhysics();

		void RegisterRigidBodyBox(RigidBodyComponent* bodyComponent, Transform* transform, const glm::vec2& boxSize, const RigidBodyComponent::BodySettings&
		                          settings, const RigidBodyComponent::PhysicsSettings& pSettings);
		void DestroyComponent(RigidBodyComponent* bodyComponent);


		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;

	private:
		class PhysicsEngineImpl;
		std::unique_ptr<PhysicsEngineImpl> m_Impl;
	};
}
