#include "PhysicsEngine.h"

#include <algorithm>
#include <functional>
#include <box2d/box2d.h>

#include "GameTime.h"
#include "RigidBodyComponent.h"


using namespace vic;

class PhysicsEngine::PhysicsEngineImpl final
{
public:
	PhysicsEngineImpl();

	void UpdatePhysics();

	void RegisterRigidBodyBox(RigidBodyComponent* bodyComponent, Transform* transform, const glm::vec2& boxSize, const RigidBodyComponent::BodySettings&
	                          settings, const RigidBodyComponent::PhysicsSettings& pSettings);
	void DestroyComponent(RigidBodyComponent* bodyComponent);


private:
	b2BodyType VicBodyTypeToB2BodyType(RigidBodyComponent::bodyType type);
private:
	std::unique_ptr<b2World> m_PhysicsWorld;
	std::unordered_map<RigidBodyComponent*, std::unique_ptr<b2Body, std::function<void(b2Body*)>>> m_RigidBodies;
};

PhysicsEngine::PhysicsEngineImpl::PhysicsEngineImpl()
	:m_PhysicsWorld{std::make_unique<b2World>(b2Vec2{0.f, 0.f})}
{
}

void PhysicsEngine::PhysicsEngineImpl::UpdatePhysics()
{
	constexpr int32_t velocityIterations = 6;
	constexpr int32_t positionIterations = 2;
	m_PhysicsWorld->Step(static_cast<float>(GameTime::GetInstance().GetFixedTimeStep()),
		velocityIterations, positionIterations);



	constexpr auto applyPhysics = [](auto& body)
		{
			glm::vec2 newPos{};
			newPos.x = body.second->GetPosition().x;
			newPos.y = body.second->GetPosition().y;

			float newRot{ body.second->GetAngle() };

			body.first->ApplyPhysicsMovement(newPos, newRot);
		};

	std::ranges::for_each(m_RigidBodies, applyPhysics);
}

void PhysicsEngine::PhysicsEngineImpl::RegisterRigidBodyBox(RigidBodyComponent* bodyComponent,
	Transform* transform, const glm::vec2& boxSize, const RigidBodyComponent::BodySettings& settings
	, const RigidBodyComponent::PhysicsSettings& pSettings)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(transform->Position().x, transform->Position().y);
	bodyDef.angle = transform->Rotation();

	bodyDef.type = VicBodyTypeToB2BodyType(settings.type);
	bodyDef.allowSleep = settings.allowSleep;
	bodyDef.awake = settings.awake;
	bodyDef.fixedRotation = settings.fixedRotation;
	bodyDef.bullet = settings.bulletProcessing;
	bodyDef.enabled = settings.enabled;
	bodyDef.gravityScale = settings.gravityScale;

	b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);


	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(boxSize.x, boxSize.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = pSettings.density;
	fixtureDef.friction = pSettings.friction;
	fixtureDef.restitution = pSettings.restitution;
	fixtureDef.restitutionThreshold = pSettings.restitutionThreshold;

	body->CreateFixture(&fixtureDef);
	body->SetTransform({ transform->Position().x, transform->Position().y }, transform->Rotation());

	std::unique_ptr<b2Body, std::function<void(b2Body*)>> bodyPtr
	{
		body,
		[this](b2Body* body)
		{
			m_PhysicsWorld->DestroyBody(body);
		}
	};


	m_RigidBodies[bodyComponent] = std::move(bodyPtr);
}

void PhysicsEngine::PhysicsEngineImpl::DestroyComponent(RigidBodyComponent* bodyComponent)
{
	m_RigidBodies.erase(bodyComponent);
}

b2BodyType PhysicsEngine::PhysicsEngineImpl::VicBodyTypeToB2BodyType(RigidBodyComponent::bodyType type)
{
	switch (type)
	{
	case RigidBodyComponent::bodyType::staticBody:
		return b2_staticBody;
	case RigidBodyComponent::bodyType::dynamicBody:
		return b2_dynamicBody;
	case RigidBodyComponent::bodyType::kinematicBody:
		return b2_kinematicBody;
	}
}


//PhysicsEngine
PhysicsEngine::PhysicsEngine()
	:m_Impl{std::make_unique<PhysicsEngineImpl>()}
{
}

PhysicsEngine::~PhysicsEngine() = default;

void PhysicsEngine::UpdatePhysics()
{
	m_Impl->UpdatePhysics();
}

void PhysicsEngine::RegisterRigidBodyBox(RigidBodyComponent* bodyComponent,
	Transform* transform, const glm::vec2& boxSize, const RigidBodyComponent::BodySettings& settings
	, const RigidBodyComponent::PhysicsSettings& pSettings)
{
	m_Impl->RegisterRigidBodyBox(bodyComponent, transform, boxSize, settings, pSettings);
}

void PhysicsEngine::DestroyComponent(RigidBodyComponent* bodyComponent)
{
	m_Impl->DestroyComponent(bodyComponent);
}

