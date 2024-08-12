#pragma once
#include "BaseComponent.h"

class EnemyLogicComp : public vic::BaseComponent
{
public:
	EnemyLogicComp(vic::GameObject* ownerPtr);

	void Hit();
private:
	int m_LivesLeft;
};
