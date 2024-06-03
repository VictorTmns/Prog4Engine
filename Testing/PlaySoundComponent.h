#pragma once
#include "BaseComponent.h"

class PlaySoundComponent : public vic::BaseComponent
{
public:
	PlaySoundComponent(vic::GameObject* owner);
	void PlaySound();

private:
	unsigned m_SoundId;
};
