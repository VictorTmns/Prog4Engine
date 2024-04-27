#pragma once
#include <string>
#include <memory>
#include "ISoundSystem.h"

namespace minigin
{

	class SoundSystemSDL final : public ISoundSystem
	{
	public:
		SoundSystemSDL();
		~SoundSystemSDL() override;

		SoundSystemSDL(const SoundSystemSDL&) = delete;
		SoundSystemSDL(SoundSystemSDL&&) = delete;
		SoundSystemSDL& operator=(const SoundSystemSDL&) = delete;
		SoundSystemSDL& operator=(SoundSystemSDL&&) = delete;

		unsigned int LoadSound(const std::string& path) override;
		void PlaySound(unsigned soundID, float volume) override;

	private:
		class SDLImpl;
		std::unique_ptr<SDLImpl> m_Impl;
	};
}
