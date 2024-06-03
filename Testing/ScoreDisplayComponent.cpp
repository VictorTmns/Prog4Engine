#include "ScoreDisplayComponent.h"

#include <string>

#include "GameObject.h"
#include "ScoreComponent.h"

ScoreDisplayComponent::ScoreDisplayComponent(vic::GameObject* owner, vic::Font* font)
	: BaseComponent{owner}
	, Observer{}
	, m_TextRenderer{ owner->AddComponent<vic::TextRenderComponent>(font) }
{
}

void ScoreDisplayComponent::Notify(Event event, const vic::BaseComponent* actorComponent)
{
	if (event != Event::scoreChange && event != Event::subjectAttached)
		return;

	int currentScore = dynamic_cast<const ScoreComponent*>(actorComponent)->GetScore();

	m_TextRenderer->SetText("score: " + std::to_string(currentScore));

}
