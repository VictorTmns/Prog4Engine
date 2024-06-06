#pragma once
#include <iostream>
#include <memory>

#include "ISoundSystem.h"

namespace vic
{
	class SoundLogWrapper final : public ISoundSystem
	{
	public:
		SoundLogWrapper(std::unique_ptr<ISoundSystem> soundImpl)
			: m_SoundImpl{ soundImpl }
		{}

		void PlaySound(unsigned soundID, float volume) override
		{
			std::cout << "playing sound :" + std::to_string(soundID) + " at volume: " + std::to_string(volume) + "\n";
			m_SoundImpl->PlaySound(soundID, volume);
		}


		unsigned LoadSound(const std::string& path) override
		{
			const unsigned id = m_SoundImpl->LoadSound(path);
			std::cout << "sound loaded from: '" + path + "' and assigned id: " + std::to_string(id) + "\n";
			return id;
		}

	private:
		std::unique_ptr<ISoundSystem> m_SoundImpl;
	};
}