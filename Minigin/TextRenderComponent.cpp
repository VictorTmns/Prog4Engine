#include <stdexcept>
#include <SDL_ttf.h>
#include "TextRenderComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "Texture2D.h"

minigin::TextRenderComponent::TextRenderComponent(GameObject* owner, Font* font, const std::string& text, TextAlignment alignment)
	: BaseComponent{owner}
	, m_needsUpdate(true)
	, m_text(text)
	, m_font(font)
	, m_textTexture(nullptr)
	, m_Alignment{alignment}
{ }

void minigin::TextRenderComponent::Update()
{
	if (m_needsUpdate && !m_text.empty())
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_unique<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void minigin::TextRenderComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		auto pos = GetOwner()->GetWorldTransform().GetPosition();

		switch (m_Alignment) {
		case TextAlignment::center:
			break;
		case TextAlignment::left:
			pos.x -= static_cast<float>(m_textTexture->GetSize().x) / 2.f;
			break;
		case TextAlignment::right:
			pos.x += static_cast<float>(m_textTexture->GetSize().x) / 2.f;
			break;
		}

		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void minigin::TextRenderComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}


