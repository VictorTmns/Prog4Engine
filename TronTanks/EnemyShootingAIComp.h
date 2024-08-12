#pragma once
#include "BarrelComponent.h"
#include "BaseComponent.h"
#include "OverlapComponent.h"

class EnemyShootingAIComp : public vic::BaseComponent
{
public:
	EnemyShootingAIComp(vic::GameObject* ownerPtr, BarrelComponent* barrelPtr);
	void OnStart() override;
	void Update() override;
private:
	BarrelComponent* m_BarrelComp;
	float m_ElapsedSec;
	float m_ShootingCooldown;

	std::vector<vic::OverlapComponent*> m_Targets;
};
