#include "ScoreComponent.h"


void ScoreComponent::ChangeScore(int scoreChange)
{
	m_Score += scoreChange;
	NotifyObservers(minigin::Observer::Event::scoreChange);
}


ScoreComponent::ScoreComponent(minigin::GameObject* owner)
	: BaseComponent{owner}
	, m_Score{0}
{
}
