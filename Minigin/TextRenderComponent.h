#pragma once
#include <string>
#include <memory>

#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"

namespace vic
{
	class Font;
	class TextRenderComponent final : public BaseComponent
	{
	public:
		enum class TextAlignment
		{
			center,
			left,
			right
		};


		void Render(const Renderer* renderer) const override;

		void SetText(const std::string& text);

		TextRenderComponent(GameObject* owner, Font* font, const std::string& text = {}, TextAlignment alignment = TextAlignment::center);
	private:
		bool m_needsUpdate;
		std::string m_text;
		Font* m_font;
		TextAlignment m_Alignment;
	};
}
