#include "EnemyShootingAIComp.h"

#include "GameTime.h"
#include "Scene.h"

EnemyShootingAIComp::EnemyShootingAIComp(vic::GameObject* ownerPtr, BarrelComponent* barrelPtr)
	: BaseComponent{ownerPtr}
	  , m_BarrelComp{barrelPtr}, m_ElapsedSec{0}, m_ShootingCooldown{1}
{
}

void EnemyShootingAIComp::OnStart()
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


	m_ElapsedSec = 0.f;

	auto pos{ m_BarrelComp->Owner()->GetTransform().Position() };
	for (const auto & target : m_Targets)
	{
		glm::vec2 targetPos{ target->Owner()->GetTransform().Position() + target->GetDimensions()/2.f };
		if(abs(targetPos.x - pos.x) < target->GetDimensions().x / 2.f)
		{
			if (pos.y < targetPos.y)
				m_BarrelComp->Shoot(BarrelComponent::Direction::down, 200);
			else
				m_BarrelComp->Shoot(BarrelComponent::Direction::up, 200);

		}
		else if(abs(targetPos.y - pos.y) < target->GetDimensions().y / 2.f)
		{
			if (pos.x < targetPos.x)
				m_BarrelComp->Shoot(BarrelComponent::Direction::right, 200);
			else
				m_BarrelComp->Shoot(BarrelComponent::Direction::left, 200);
		}
	}
}
