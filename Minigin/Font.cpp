#include <stdexcept>
#include "Font.h"

#include <memory>

#include "SDL_FontCache.h"

vic::Font::Font(SDL_Renderer* renderer, std::string fullPath, unsigned int size) 
	: m_font(nullptr)
{
	m_font = FC_CreateFont();
	if (FC_LoadFont(m_font, renderer, fullPath.data(), size, SDL_Color{ 255, 255, 255, 255 }, TTF_STYLE_NORMAL) == 0)
	{
		throw std::runtime_error("SDL_FontCache error: failed to load font: \" " + fullPath + " \" \n");
	}
}

vic::Font::~Font()
{
	FC_FreeFont(m_font);
}

void vic::Font::Draw(const std::string& text, const Renderer* renderer, float x, float y) const
{
	FC_Draw(m_font, renderer->GetSDLRenderer(),x, y, text.data());
}

