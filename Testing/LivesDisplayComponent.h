#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Observer.h"
#include "ResourceManager.h"

namespace vic
{
	class TextRenderComponent;

	class LivesDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		LivesDisplayComponent(GameObject* owner, Font* font);

		void Notify(Event event, const vic::BaseComponent* actorComponent) override;

	private:
		TextRenderComponent* m_TextRenderer;
	};
}
