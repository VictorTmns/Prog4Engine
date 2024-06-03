#include <SDL.h>
#include "Texture2D.h"

#include <SDL_image.h>
#include <stdexcept>
#include <string>

#include "Renderer.h"

vic::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 vic::Texture2D::GetSize() const
{
	SDL_Rect dst{};
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* vic::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

vic::Texture2D::Texture2D(const std::string& fullPath, SDL_Renderer* sdlRenderer)
{
	m_texture = IMG_LoadTexture(sdlRenderer, fullPath.c_str());
	if (m_texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
}


void vic::Texture2D::Draw(const Renderer* renderer, float x, float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(m_texture, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(renderer->GetSDLRenderer(), m_texture, nullptr, &dst);
}

void vic::Texture2D::Draw(const Renderer* renderer, float x, float y, float width, float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(renderer->GetSDLRenderer(), m_texture, nullptr, &dst);
}