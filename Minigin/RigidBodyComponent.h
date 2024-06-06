#pragma once

#include "BaseComponent.h"
#include "Transform.h"

class b2Body;

namespace vic
{
	class RigidBodyComponent : public BaseComponent
	{
	public:
		enum class bodyType
		{
			staticBody,
			dynamicBody,
			kinematicBody,

		};

		struct BodySettings
		{
			bool allowSleep = true;
			bool awake = true;
			bool fixedRotation = false;
			bool bulletProcessing = false;
			bodyType type = bodyType::staticBody;
			bool enabled = true;
			float gravityScale = 1.0f;

			BodySettings() = default;
		};

		struct PhysicsSettings
		{
			float density = 1.f;
			float friction = 0.f;
			float restitution = 0.f;
			float restitutionThreshold = 0.f;

			PhysicsSettings() = default;
		};


		RigidBodyComponent(GameObject* ownerPtr, const glm::vec2& boxSize, const BodySettings& settings = {}, const PhysicsSettings& pSettings = {});
		~RigidBodyComponent() override;

		void ApplyForceToCenter(const glm::vec2& force);
		void ApplyForceToPoint(const glm::vec2& force, const glm::vec2& point);
		void ApplyTorque(float torque);

		glm::vec2 GetVelocity();
		float GetAngularVelocity();
		float GetGravityScale();
		float GetInertia();

		// This function is a callback
		// DON'T CALL IT
		void ApplyPhysicsMovementCallback(const glm::vec2& pos, const float rot);
	private:
		Transform* m_GOTranformPtr;
	};

}