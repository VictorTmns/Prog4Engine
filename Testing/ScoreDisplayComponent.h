#pragma once
#include "BaseComponent.h"
#include "TextRenderComponent.h"




class ScoreDisplayComponent final : public vic::BaseComponent, public vic::Observer
{
public:
	ScoreDisplayComponent(vic::GameObject* owner, vic::Font* font);

	void Notify(Event event, const vic::BaseComponent* actorComponent) override;

private:
	vic::TextRenderComponent* m_TextRenderer;
};
