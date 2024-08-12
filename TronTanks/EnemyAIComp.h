#pragma once
#include "BarrelComponent.h"
#include "BaseComponent.h"
#include "MovementComponent.h"

class EnemyAIComp : public vic::BaseComponent
{
public:
	EnemyAIComp(vic::GameObject* ownerPtr, MovementComponent* movComp, BarrelComponent* barrelComp);
	
	void Hit();
private:
	MovementComponent* m_MovComp;
	BarrelComponent* m_BarrelComp;

	int m_LivesLeft;
};
