#pragma once
#include "BarrelComponent.h"
#include "BaseComponent.h"
#include "OverlapComponent.h"

class EnemyShootingAIComp : public vic::BaseComponent
{
public:
	EnemyShootingAIComp(vic::GameObject* ownerPtr, BarrelComponent* barrelPtr);
	void OnSceneStart() override;
	void Update() override;
	void TryShoot(::BarrelComponent::Direction dir, const glm::vec2& targetPos);

private:
	BarrelComponent* m_BarrelComp;
	float m_ElapsedSec;
	float m_ShootingCooldown;

	std::vector<vic::OverlapComponent*> m_Targets;
};
