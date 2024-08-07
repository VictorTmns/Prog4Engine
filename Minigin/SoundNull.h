﻿#pragma once
#include "ISoundSystem.h"

namespace vic
{
	class SoundNull final : public ISoundSystem
	{
	public:
		void PlaySound(unsigned, float) override {}
		unsigned LoadSound(const std::string&) override { return std::numeric_limits<unsigned int>::max(); }
	};
}