#include "ServiceLocator.h"

#include "SoundNull.h"


std::unique_ptr<ISoundSystem> vic::ServiceLocator::m_SoundSystemInstance{ std::make_unique<SoundNull>() };
