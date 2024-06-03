#include "ScoreTestComponent.h"

ScoreTestComponent::ScoreTestComponent(vic::GameObject* owner, ScoreComponent* scoreComponent)
	: BaseComponent{owner}
	, m_ScoreComponent{ scoreComponent }
{
}

void ScoreTestComponent::KillEnemy()
{
	// Handle Enemy kill

	m_ScoreComponent->ChangeScore(50);
}

void ScoreTestComponent::PickUpItem()
{
	// Handle item pickup

	m_ScoreComponent->ChangeScore(100);
}
