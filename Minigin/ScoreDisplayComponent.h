#pragma once
#include "BaseComponent.h"

namespace minigin
{
	class Font;
	class TextRenderComponent;

	class ScoreDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		ScoreDisplayComponent(GameObject* owner, Font* font);

		void Notify(Event event, const minigin::BaseComponent* actorComponent) override;

	private:
		TextRenderComponent* m_TextRenderer;
	};
}
