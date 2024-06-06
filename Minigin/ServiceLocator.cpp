#include "ServiceLocator.h"

#include "SoundNull.h"
using namespace vic;


std::unique_ptr<ISoundSystem> ServiceLocator::m_SoundSystemInstance{ std::make_unique<SoundNull>() };
