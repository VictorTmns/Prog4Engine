#pragma once
#include <xstring>

#include "Renderer.h"
#include "glm/vec2.hpp"

struct SDL_Texture;
namespace vic
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		Texture2D(const std::string& fullPath, SDL_Renderer* renderer);
		~Texture2D();

		void Draw(const Renderer* renderer, float x, float y) const;
		void Draw(const Renderer* renderer, float x, float y, float width, float height) const;

		glm::ivec2 GetSize() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

	private:
		SDL_Texture* m_texture;
	};
}
