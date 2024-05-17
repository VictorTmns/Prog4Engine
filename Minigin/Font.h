#pragma once
#include <SDL_render.h>
#include <string>

#include "Renderer.h"

struct FC_Font;
namespace minigin
{
	class Font final
	{
	public:
		Font(SDL_Renderer* renderer, std::string fullPath, unsigned size);
		~Font();

		void Draw(const std::string& text, const Renderer* renderer, float x, float y) const;

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;

	private:
		FC_Font* m_font;
	};
}
