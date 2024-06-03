#pragma once
#include "BaseComponent.h"


class ScoreComponent : public vic::BaseComponent
{
public:
	ScoreComponent(vic::GameObject* owner);

	void ChangeScore(int scoreChange);
	int GetScore() const { return m_Score; }
private:
	int m_Score;
};
