#pragma once
#include <string>
namespace vic
{
	class ISoundSystem
	{
	public:
		virtual ~ISoundSystem() = default;
	
		virtual void PlaySound(unsigned soundID, float volume) = 0;
		virtual unsigned LoadSound(const std::string& path) = 0;
	};

}