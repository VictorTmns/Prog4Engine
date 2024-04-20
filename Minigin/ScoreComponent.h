#pragma once
#include "BaseComponent.h"


class ScoreComponent : public minigin::BaseComponent
{
public:
	ScoreComponent(minigin::GameObject* owner);

	void ChangeScore(int scoreChange);
	int GetScore() const { return m_Score; }
private:
	int m_Score;
};
