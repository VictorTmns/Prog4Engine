#include "ServiceLocator.h"

#include "SoundNull.h"


std::unique_ptr<ISoundSystem> minigin::ServiceLocator::m_SoundSystemInstance{ std::make_unique<SoundNull>() };
