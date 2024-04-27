#pragma once
#include "BaseComponent.h"

class PlaySoundComponent : public minigin::BaseComponent
{
public:
	PlaySoundComponent(minigin::GameObject* owner);
	void PlaySound();

private:
	unsigned m_SoundId;
};
