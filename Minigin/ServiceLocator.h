#pragma once
#include <memory>

#include "ISoundSystem.h"

namespace minigin
{
	class ServiceLocator final
	{
	public:
		static ISoundSystem& GetSoundSystem() { return *m_SoundSystemInstance;}
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem)
			{ m_SoundSystemInstance = std::move(soundSystem); }
	private:
		static std::unique_ptr<ISoundSystem> m_SoundSystemInstance;
		
	};
}