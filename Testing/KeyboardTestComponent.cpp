﻿#include "KeyboardTestComponent.h"

#include "GameObject.h"
#include "GameTime.h"

KeyboardTestComponent::KeyboardTestComponent(minigin::GameObject* owner)
	: BaseComponent{owner}
	, m_Speed{80.f}
{
}

void KeyboardTestComponent::Move(float x, float y)
{
	GetOwner()->AddLocalTranslate(
		x * m_Speed * static_cast<float>(GameTime::GetInstance().GetDeltaTime()),
		y * m_Speed * static_cast<float>(GameTime::GetInstance().GetDeltaTime())
	);
}