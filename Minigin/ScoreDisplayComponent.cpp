#include "ScoreDisplayComponent.h"

#include <string>

#include "GameObject.h"
#include "ScoreComponent.h"
#include "TextRenderComponent.h"

minigin::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* owner, Font* font)
	: BaseComponent{owner}
	, Observer{}
	, m_TextRenderer{ owner->AddComponent<TextRenderComponent>(font) }
{
}

void minigin::ScoreDisplayComponent::Notify(Event event, const minigin::BaseComponent* actorComponent)
{
	if (event != Event::scoreChange && event != Event::subjectAttached)
		return;

	int currentScore = dynamic_cast<const ScoreComponent*>(actorComponent)->GetScore();

	m_TextRenderer->SetText("score: " + std::to_string(currentScore));

}
