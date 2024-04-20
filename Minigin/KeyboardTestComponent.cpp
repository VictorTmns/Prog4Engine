#include "KeyboardTestComponent.h"

#include "GameObject.h"
#include "Time.h"

KeyboardTestComponent::KeyboardTestComponent(minigin::GameObject* owner)
	: BaseComponent{owner}
	, m_Speed{80.f}
{
}

void KeyboardTestComponent::Move(float x, float y)
{
	GetOwner()->AddLocalTranslate(
		x * m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime()),
		y * m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime())
	);
}
