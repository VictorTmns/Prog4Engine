#include "LivesDisplayComponent.h"

#include "Font.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "TextRenderComponent.h"


namespace minigin
{
	LivesDisplayComponent::LivesDisplayComponent(GameObject* owner, Font* font)
	: BaseComponent{owner}
	, Observer{}
	, m_TextRenderer{owner->AddComponent<TextRenderComponent>(font)}
	{
	}

	void LivesDisplayComponent::Notify(Event event, const minigin::BaseComponent* actorComponent)
	{
		if(event != Event::playerHealthChanges && event != Event::subjectAttached)
			return;

		int nrOfRemainingLives = dynamic_cast<const LivesComponent*>(actorComponent)->GetNrOfLives();

		m_TextRenderer->SetText("#lives: " + std::to_string(nrOfRemainingLives));
	}
}
