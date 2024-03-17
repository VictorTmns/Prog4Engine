#include <SDL.h>
#include "Texture2D.h"

minigin::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 minigin::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* minigin::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

minigin::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_texture = texture;
}
