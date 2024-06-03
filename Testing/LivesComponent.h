#pragma once
#include "BaseComponent.h"


class LivesComponent final : public vic::BaseComponent
{
public:
	LivesComponent(vic::GameObject* owner, int maxLives);

	int GetNrOfLives() const { return m_NrOfRemainingLives; }

	void TakeDamage();
private:
	int m_NrOfRemainingLives;
	int m_MaxNrOfLives;
};
