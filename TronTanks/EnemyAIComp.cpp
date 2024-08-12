#include "EnemyAIComp.h"

EnemyAIComp::EnemyAIComp(vic::GameObject* ownerPtr, MovementComponent* movComp, BarrelComponent* barrelComp)
	: BaseComponent{ownerPtr}, m_MovComp{movComp}, m_BarrelComp{barrelComp}, m_LivesLeft{3}
{
}

void EnemyAIComp::Hit()
{
	m_LivesLeft--;
	if (m_LivesLeft == 0) Owner()->Destroy();
}
