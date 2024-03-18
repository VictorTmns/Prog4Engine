#pragma once
#include <memory>
#include <SDL.h>
#include <glm/vec2.hpp>

#include "Singleton.h"

namespace minigin
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;


		void RenderCircle(float xCenter, float yCenter, float radius, SDL_Color color);
		void RenderRect(float left, float top, float width, float height, SDL_Color color);
		void FillCircle(float x, float y, float radius, SDL_Color color);

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

