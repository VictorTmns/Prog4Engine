#include "LivesComponent.h"

LivesComponent::LivesComponent(minigin::GameObject* owner, int maxLives)
	: BaseComponent{owner}
	, m_MaxNrOfLives{maxLives}
	, m_NrOfRemainingLives{maxLives}
{
}

void LivesComponent::TakeDamage()
{
	if (m_NrOfRemainingLives <= 0)
		return;

	m_NrOfRemainingLives--;
	NotifyObservers(minigin::Observer::Event::playerHealthChanges);
}
