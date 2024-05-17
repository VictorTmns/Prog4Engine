#pragma once
#include "BaseComponent.h"


class LivesComponent final : public minigin::BaseComponent
{
public:
	LivesComponent(minigin::GameObject* owner, int maxLives);

	int GetNrOfLives() const { return m_NrOfRemainingLives; }

	void TakeDamage();
private:
	int m_NrOfRemainingLives;
	int m_MaxNrOfLives;
};
