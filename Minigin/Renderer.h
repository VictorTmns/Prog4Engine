#pragma once
#include <memory>
#include <SDL.h>
#include <glm/vec2.hpp>

namespace minigin
{
	class Renderer final
	{
	public:
		Renderer();
		~Renderer();

		void Render() const;


		void RenderCircle(float xCenter, float yCenter, float radius, SDL_Color color) const;
		void RenderRect(float left, float top, float width, float height, SDL_Color color) const;
		void FillCircle(float x, float y, float radius, SDL_Color color) const;

		SDL_Renderer* GetSDLRenderer() const;

		void SetDrawColor(int r, int g, int b, int a = 255) const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

	private:


		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
	};
}

