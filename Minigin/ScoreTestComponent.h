#pragma once
#include "BaseComponent.h"
#include "ScoreComponent.h"

class ScoreTestComponent : public minigin::BaseComponent
{
public:
	ScoreTestComponent(minigin::GameObject* owner, ScoreComponent* scoreComponent);

	void KillEnemy();
	void PickUpItem();
private:
	ScoreComponent* m_ScoreComponent;
};
