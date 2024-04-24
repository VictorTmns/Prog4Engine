#include "LivesComponent.h"

minigin::LivesComponent::LivesComponent(GameObject* owner, int maxLives)
	: BaseComponent{owner}
	, m_MaxNrOfLives{maxLives}
	, m_NrOfRemainingLives{maxLives}
{
}

void minigin::LivesComponent::TakeDamage()
{
	if (m_NrOfRemainingLives <= 0)
		return;

	m_NrOfRemainingLives--;
	NotifyObservers(Observer::Event::playerHealthChanges);
}
