#pragma once
#include <map>
#include <string>
#include <memory>
#include "Singleton.h"

#include "Texture2D.h"
#include "Font.h"

namespace minigin
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& dataPath, Renderer* rendererPtr);

		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);
	private:
		std::map<const std::string, std::unique_ptr<Texture2D>> m_LoadedTextures;
		std::map<const std::string, std::unique_ptr<Font>> m_LoadedFonts;

		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
		Renderer* m_RendererPtr = nullptr;
	};
}
