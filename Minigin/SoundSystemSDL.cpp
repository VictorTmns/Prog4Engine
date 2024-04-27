#include "SoundSystemSDL.h"

#include <assert.h>
#include <iostream>
#include <SDL.h>
#include <stdexcept>

#include <SDL_mixer.h>


minigin::SoundSystemSDL::SoundSystemSDL()
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

minigin::SoundSystemSDL::~SoundSystemSDL()
{
	for (Mix_Chunk* loadedSound : m_LoadedSounds)
	{
		Mix_FreeChunk(loadedSound);
	}
	Mix_Quit();
}


unsigned int minigin::SoundSystemSDL::LoadSound(const std::string& path)
{
	if(const auto id = m_SoundTable.find(path); id != m_SoundTable.end())
    {
        return id->second;
    }


	if(SDLLoadSound(path))
	{
		const unsigned int soundID{ static_cast<unsigned>(m_LoadedSounds.size() - 1) };
        m_SoundTable[path] = soundID;
        return soundID;
	}


	return 0;
}

void minigin::SoundSystemSDL::PlaySound(unsigned soundID, float volumePercentage = 1)
{
    m_ThreadedTaskProcessor->AddTask(SoundCommand{ soundID, volumePercentage });
}


bool minigin::SoundSystemSDL::ProcessSoundRequest(const SoundCommand& command) const
{
    const int usedChannel = Mix_PlayChannel(-1, m_LoadedSounds[command.id], 0);
    Mix_Volume(usedChannel, int(command.volume * MIX_MAX_VOLUME));
    
    return (usedChannel != -1);
}


bool minigin::SoundSystemSDL::SDLLoadSound(const std::string& path)
{
    Mix_Chunk* loadedSound = Mix_LoadWAV(path.data());

    if(loadedSound == NULL)
    {
	    assert(false);
        std::cout << "failed to load sound: " + path + "\n";
        return false;
    }

    m_LoadedSounds.push_back(loadedSound);
    return true;
}

