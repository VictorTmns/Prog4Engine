#include "ScoreComponent.h"


void ScoreComponent::ChangeScore(int scoreChange)
{
	m_Score += scoreChange;
	NotifyObservers(vic::Observer::Event::scoreChange);
}


ScoreComponent::ScoreComponent(vic::GameObject* owner)
	: BaseComponent{owner}
	, m_Score{0}
{
}
