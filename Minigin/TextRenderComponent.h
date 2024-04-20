#pragma once
#include <string>
#include <memory>

#include "BaseComponent.h"
#include "Texture2D.h"
#include "Transform.h"

namespace minigin
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

		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);

		TextRenderComponent(GameObject* owner, Font* font, const std::string& text = {}, TextAlignment alignment = TextAlignment::center);
	private:
		bool m_needsUpdate;
		std::string m_text;
		Font* m_font;
		std::unique_ptr<Texture2D> m_textTexture;
		TextAlignment m_Alignment;
	};
}
