#include "EnemyShootingAIComp.h"

#include "BarrelComponent.h"
#include "BarrelComponent.h"
#include "BarrelComponent.h"
#include "BarrelComponent.h"
#include "BarrelComponent.h"
#include "GameTime.h"
#include "Scene.h"

EnemyShootingAIComp::EnemyShootingAIComp(vic::GameObject* ownerPtr, BarrelComponent* barrelPtr)
	: BaseComponent{ownerPtr}
	  , m_BarrelComp{barrelPtr}, m_ElapsedSec{0}, m_ShootingCooldown{1}
{
}

void EnemyShootingAIComp::OnSceneStart()
{
	for (vic::GameObject* go : Owner()->GetScene()->GetGameObjectsByName("player"))
	{
		m_Targets.push_back(go->GetComponent<vic::OverlapComponent>());
	}
	
}

void EnemyShootingAIComp::Update()
{
	m_ElapsedSec += static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime());

	if(m_ElapsedSec < m_ShootingCooldown)
		return;




	auto pos{ m_BarrelComp->Owner()->GetTransform().Position() };
	for (const auto & target : m_Targets)
	{
		glm::vec2 targetPos{ target->Owner()->GetTransform().Position() + target->GetDimensions()/2.f };
		if(abs(targetPos.x - pos.x) < target->GetDimensions().x / 2.f)
		{
			if (pos.y < targetPos.y)
				TryShoot(BarrelComponent::Direction::down, targetPos);
			else
				TryShoot(BarrelComponent::Direction::up, targetPos);
		}
		else if(abs(targetPos.y - pos.y) < target->GetDimensions().y / 2.f)
		{
			if (pos.x < targetPos.x)
				TryShoot(BarrelComponent::Direction::right, targetPos);
			else
				TryShoot(BarrelComponent::Direction::left, targetPos);
		}
	}
}

void EnemyShootingAIComp::TryShoot(BarrelComponent::Direction dir, const glm::vec2& targetPos)
{
	if(Owner()->GetScene()->GetPhysicsEngine().CollidesWithStatics(
		Owner()->GetTransform().Position(), targetPos - Owner()->GetTransform().Position()))
		return;

	m_ElapsedSec = 0.f;
	m_BarrelComp->Shoot(dir, 200);
}