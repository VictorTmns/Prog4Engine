#pragma once
#include <string>
#include <memory>

#include "BaseComponent.h"
#include "Transform.h"

namespace minigin
{
	class Font;
	class Texture2D;
	class TextRenderComponent final : public BaseComponent
	{
	public:
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);

		TextRenderComponent(GameObject* owner, Font* font, const std::string& text = {});
		~TextRenderComponent() override = default;
	private:
		bool m_needsUpdate;
		std::string m_text;
		Font* m_font;
		std::unique_ptr<Texture2D> m_textTexture;
	};
}
