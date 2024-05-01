#include "SoundSystemSDL.h"

#include <cassert>
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdexcept>
#include "ThreadQueueWorker.h"

#include <unordered_map>

namespace minigin
{
	// PIPMP IMPL
	class SoundSystemSDL::SDLImpl final : public ISoundSystem
	{
	public:
		SDLImpl();
		~SDLImpl() override;

		SDLImpl(const SDLImpl&) = delete;
		SDLImpl(SDLImpl&&) = delete;
		SDLImpl& operator=(const SDLImpl&) = delete;
		SDLImpl& operator=(SDLImpl&&) = delete;

		unsigned int LoadSound(const std::string& path) override;
		void PlaySound(unsigned soundID, float volume) override;

	private:
		struct SoundCommand
		{
			unsigned int id;
			float volume;

			bool operator==(const SoundCommand& other) const
			{
				return (this->id == other.id);
			}
		};

		bool ProcessSoundRequest(const SoundCommand& command) const;

		bool SDLLoadSound(const std::string& path);



		std::unique_ptr<ThreadQueueWorker<SoundCommand>> m_ThreadedTaskProcessor;

		std::unordered_map<std::string, unsigned int> m_SoundTable;
		std::vector<Mix_Chunk*> m_LoadedSounds;
	};

	SoundSystemSDL::SDLImpl::SDLImpl()
	{
		//Initialize all SDL subsystems
		if (SDL_Init(SDL_INIT_AUDIO) != 0)
		{
			throw std::runtime_error(std::string("SDL_mixer_Init Error: ") + SDL_GetError());
		}
		//Initialize SDL_mixer
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
		{
			throw std::runtime_error(std::string("SDL_mixer_Init Error: ") + Mix_GetError());
		}



		std::function soundProcessFunc = [this](const SoundCommand& task) -> bool
			{ return this->ProcessSoundRequest(task); };

		m_ThreadedTaskProcessor
			= std::make_unique<ThreadQueueWorker<SoundCommand>>(soundProcessFunc);
	}

	SoundSystemSDL::SDLImpl::~SDLImpl()
	{
		for (Mix_Chunk* loadedSound : m_LoadedSounds)
		{
			Mix_FreeChunk(loadedSound);
		}
		Mix_Quit();
	}


	unsigned int SoundSystemSDL::SDLImpl::LoadSound(const std::string& path)
	{
		if (const auto id = m_SoundTable.find(path); id != m_SoundTable.end())
		{
			return id->second;
		}


		if (SDLLoadSound(path))
		{
			const unsigned int soundID{ static_cast<unsigned>(m_LoadedSounds.size() - 1) };
			m_SoundTable[path] = soundID;
			return soundID;
		}


		return 0;
	}

	void SoundSystemSDL::SDLImpl::PlaySound(unsigned soundID, float volumePercentage = 1)
	{
		m_ThreadedTaskProcessor->AddTask(SoundCommand{ soundID, volumePercentage });
	}


	bool SoundSystemSDL::SDLImpl::ProcessSoundRequest(const SoundCommand& command) const
	{
		const int usedChannel = Mix_PlayChannel(-1, m_LoadedSounds[command.id], 0);
		Mix_Volume(usedChannel, int(command.volume * MIX_MAX_VOLUME));

		return (usedChannel != -1);
	}


	bool SoundSystemSDL::SDLImpl::SDLLoadSound(const std::string& path)
	{
		Mix_Chunk* loadedSound = Mix_LoadWAV(path.data());

		if (loadedSound == NULL)
		{
			assert(false);
			std::cout << "failed to load sound: " + path + "\n";
			return false;
		}

		m_LoadedSounds.push_back(loadedSound);
		return true;
	}

	//SoundSystemSDL

	SoundSystemSDL::SoundSystemSDL()
		: m_Impl{std::make_unique<SDLImpl>()}
	{
	}


	SoundSystemSDL::~SoundSystemSDL() = default;

	unsigned SoundSystemSDL::LoadSound(const std::string& path)
	{
		return m_Impl->LoadSound(path);
	}

	void SoundSystemSDL::PlaySound(unsigned soundID, float volume)
	{
		m_Impl->PlaySound(soundID, volume);
	}
}