#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Observer.h"
#include "ResourceManager.h"

namespace minigin
{
	class TextRenderComponent;

	class LivesDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		LivesDisplayComponent(GameObject* owner, Font* font);

		void Notify(Event event, const minigin::BaseComponent* actorComponent) override;

	private:
		TextRenderComponent* m_TextRenderer;
	};
}
