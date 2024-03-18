#include "KeyboardTestComponent.h"

#include "GameObject.h"
#include "Time.h"

KeyboardTestComponent::KeyboardTestComponent(minigin::GameObject* owner)
	: BaseComponent{owner}
	, m_Speed{80.f}
{
}

void KeyboardTestComponent::MoveUp()
{
	GetOwner()->AddLocalTranslate(
		0,
		-m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime())
		);
}

void KeyboardTestComponent::MoveDown()
{
	GetOwner()->AddLocalTranslate(
		0,
		m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime())
		);
}

void KeyboardTestComponent::MoveLeft()
{
	GetOwner()->AddLocalTranslate(
		-m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime()),
		0
		);
}

void KeyboardTestComponent::MoveRight()
{
	GetOwner()->AddLocalTranslate(
		m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime()),
		0
	);
}

void KeyboardTestComponent::Move(float x, float y)
{
	GetOwner()->AddLocalTranslate(
		-x * m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime()),
		y * m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime())
	);
}
