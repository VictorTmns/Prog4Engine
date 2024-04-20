#pragma once
#include "BaseComponent.h"

namespace minigin
{
	class LivesComponent final : public BaseComponent
	{
	public:
		LivesComponent(GameObject* owner, int maxLives);

		int GetNrOfLives() const { return m_NrOfRemainingLives; }

		void TakeDamage();
	private:
		int m_NrOfRemainingLives;
		int m_MaxNrOfLives;
	};

}