#pragma once
#include "BaseComponent.h"
#include "ScoreComponent.h"

class ScoreTestComponent : public vic::BaseComponent
{
public:
	ScoreTestComponent(vic::GameObject* owner, ScoreComponent* scoreComponent);

	void KillEnemy();
	void PickUpItem();
private:
	ScoreComponent* m_ScoreComponent;
};
