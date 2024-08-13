#include <stdexcept>
#include <utility>
#include <SDL_ttf.h>
#include "TextRenderComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "Texture2D.h"

vic::TextRenderComponent::TextRenderComponent(GameObject* owner, Font* font, const std::string& text, Font::TextAlignment alignment)
	: BaseComponent{owner}
	, m_Offset{0, 0}
	, m_needsUpdate(true)
	, m_text(text)
	, m_font(font)
	, m_Alignment{alignment}
{
}


void vic::TextRenderComponent::Render(const Renderer* renderer) const
{
	if (!m_text.empty())
	{
		glm::vec2 pos = Owner()->GetTransform().Position() + m_Offset;

		m_font->Draw(m_text, renderer, pos.x, pos.y, m_Alignment);
	}
}

// This implementation uses the "dirty flag" pattern
void vic::TextRenderComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}


