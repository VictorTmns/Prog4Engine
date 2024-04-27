#include "PlaySoundComponent.h"

#include "ServiceLocator.h"

PlaySoundComponent::PlaySoundComponent(minigin::GameObject* owner)
	: BaseComponent{owner}
	, m_SoundId{minigin::ServiceLocator::GetSoundSystem().LoadSound("../Data/Testing/testWav.wav")}
{
}


void PlaySoundComponent::PlaySound()
{
	minigin::ServiceLocator::GetSoundSystem().PlaySound(m_SoundId, 1);
}
