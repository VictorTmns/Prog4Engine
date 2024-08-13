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


		void Render(const Renderer* renderer) const override;

		void SetText(const std::string& text);


		void SetOffset(const glm::vec2& offset) { m_Offset = offset; }

		TextRenderComponent(GameObject* owner, Font* font, const std::string& text = {}, Font::TextAlignment alignment = Font::TextAlignment::center);
	private:
		glm::vec2 m_Offset;

		bool m_needsUpdate;
		std::string m_text;
		Font* m_font;
		Font::TextAlignment m_Alignment;
	};
}
