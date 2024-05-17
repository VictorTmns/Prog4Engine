#pragma once
#include "BaseComponent.h"
#include "TextRenderComponent.h"




class ScoreDisplayComponent final : public minigin::BaseComponent, public minigin::Observer
{
public:
	ScoreDisplayComponent(minigin::GameObject* owner, minigin::Font* font);

	void Notify(Event event, const minigin::BaseComponent* actorComponent) override;

private:
	minigin::TextRenderComponent* m_TextRenderer;
};
