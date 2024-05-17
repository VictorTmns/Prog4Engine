#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"


void minigin::ResourceManager::Init(const std::string& dataPath, Renderer* renderer)
{
	m_dataPath = dataPath;
	m_RendererPtr = renderer;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}

}

minigin::Texture2D* minigin::ResourceManager::LoadTexture(const std::string& file)
{
	auto textureIt = m_LoadedTextures.find(file);

	if (textureIt != m_LoadedTextures.end())
		return textureIt->second.get();

	auto emplaceResult = m_LoadedTextures.emplace(file, std::make_unique<Texture2D>(m_dataPath + file, m_RendererPtr->GetSDLRenderer()));

	return emplaceResult.first->second.get();
}


minigin::Font* minigin::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	auto fondIt = m_LoadedFonts.find(file + std::to_string(size));
	if (fondIt != m_LoadedFonts.end())
		return fondIt->second.get();


	auto emplaceResult = m_LoadedFonts.emplace(file, std::make_unique<Font>(m_RendererPtr->GetSDLRenderer(), m_dataPath + file, size));

	return emplaceResult.first->second.get();
}