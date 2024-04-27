#pragma once
#include <string>
#include <unordered_map>

#include "ISoundSystem.h"
#include "ThreadQueueWorker.h"

struct Mix_Chunk;
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
	struct SoundCommand
	{
		unsigned int id;
		float volume;
	};

	bool ProcessSoundRequest(const SoundCommand& command) const;

	bool SDLLoadSound(const std::string& path);



	std::unique_ptr<ThreadQueueWorker<SoundCommand>> m_ThreadedTaskProcessor;

	std::unordered_map<std::string, unsigned int> m_SoundTable;
	std::vector<Mix_Chunk*> m_LoadedSounds;
};

}
