#pragma once
#include <SDL_render.h>
#include <string>

#include "Renderer.h"

struct FC_Font;
namespace vic
{
	class Font final
	{
	public:
		Font(SDL_Renderer* renderer, std::string fullPath, unsigned size);
		~Font();


		enum class TextAlignment
		{
			center,
			left,
			right
		};

		void Draw(const std::string& text, const Renderer* renderer, float x, float y, TextAlignment alignment) const;

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;

	private:
		FC_Font* m_font;
	};
}
