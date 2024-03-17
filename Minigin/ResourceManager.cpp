#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"

void minigin::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}

}

minigin::Texture2D* minigin::ResourceManager::GetTexture(const std::string& file)
{
	auto textureIt = m_LoadedTextures.find(file);
	if (textureIt != m_LoadedTextures.end())
		return textureIt->second.get();


	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	auto emplaceResult = m_LoadedTextures.emplace(file, std::make_unique<Texture2D>(texture));
	return emplaceResult.first->second.get();
}

minigin::Font* minigin::ResourceManager::GetFont(const std::string& file, unsigned int size)
{
	auto textureIt = m_LoadedFonts.find(file);
	if (textureIt != m_LoadedFonts.end())
		return textureIt->second.get();


	const auto fullPath = m_dataPath + file;

	auto emplaceResult = m_LoadedFonts.emplace(file + std::to_string(size), std::make_unique<Font>(m_dataPath + file, size));
	return emplaceResult.first->second.get();
}