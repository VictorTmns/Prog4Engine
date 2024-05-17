#include "ScoreDisplayComponent.h"

#include <string>

#include "GameObject.h"
#include "ScoreComponent.h"

ScoreDisplayComponent::ScoreDisplayComponent(minigin::GameObject* owner, minigin::Font* font)
	: BaseComponent{owner}
	, Observer{}
	, m_TextRenderer{ owner->AddComponent<minigin::TextRenderComponent>(font) }
{
}

void ScoreDisplayComponent::Notify(Event event, const minigin::BaseComponent* actorComponent)
{
	if (event != Event::scoreChange && event != Event::subjectAttached)
		return;

	int currentScore = dynamic_cast<const ScoreComponent*>(actorComponent)->GetScore();

	m_TextRenderer->SetText("score: " + std::to_string(currentScore));

}
