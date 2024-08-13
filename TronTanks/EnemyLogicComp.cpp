#include "EnemyLogicComp.h"

#include "GameObject.h"


EnemyLogicComp::EnemyLogicComp(vic::GameObject* ownerPtr)
	: BaseComponent{ownerPtr}
	, m_LivesLeft{ 3 }
{
	
}

void EnemyLogicComp::Hit()
{
	m_LivesLeft--;
	if (m_LivesLeft == 0)
	{
		NotifyObservers(vic::Observer::Event::enemyDied);
		Owner()->Destroy();
	}
}
