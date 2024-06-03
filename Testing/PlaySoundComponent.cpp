#include "PlaySoundComponent.h"

#include "ServiceLocator.h"

PlaySoundComponent::PlaySoundComponent(vic::GameObject* owner)
	: BaseComponent{owner}
	, m_SoundId{vic::ServiceLocator::GetSoundSystem().LoadSound("../Data/Testing/testWav.wav")}
{
}


void PlaySoundComponent::PlaySound()
{
	vic::ServiceLocator::GetSoundSystem().PlaySound(m_SoundId, 1);
}
