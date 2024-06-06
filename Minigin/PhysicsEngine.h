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

		void ApplyForceToCenter(RigidBodyComponent* bodyComponent, const glm::vec2& force);
		void ApplyForceToPoint(RigidBodyComponent* bodyComponent, const glm::vec2& force, const glm::vec2& point);
		void ApplyTorque(RigidBodyComponent* bodyComponent, float torque);

		glm::vec2 GetVelocity(RigidBodyComponent* bodyComponent) const;
		float GetAngularVelocity(RigidBodyComponent* bodyComponent) const;
		float GetGravityScale(RigidBodyComponent* bodyComponent) const;
		float GetInertia(RigidBodyComponent* bodyComponent) const;


		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;

	private:
		class PhysicsEngineImpl;
		std::unique_ptr<PhysicsEngineImpl> m_Impl;
	};
}
