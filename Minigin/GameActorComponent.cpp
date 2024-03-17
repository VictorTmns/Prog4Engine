#include "GameActorComponent.h"

#include "GameObject.h"
#include "Time.h"

GameActorComponent::GameActorComponent(minigin::GameObject* owner)
	: BaseComponent{owner}
	, m_Speed{0.5f}
{
}

void GameActorComponent::MoveUp()
{
	GetOwner()->AddLocalTranslate(
		0,
		m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime())
		);
}

void GameActorComponent::MoveDown()
{
	GetOwner()->AddLocalTranslate(
		0,
		-m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime())
		);
}

void GameActorComponent::MoveLeft()
{
	GetOwner()->AddLocalTranslate(
		-m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime()),
		0
		);
}

void GameActorComponent::MoveRight()
{
	GetOwner()->AddLocalTranslate(
		m_Speed * static_cast<float>(Time::GetInstance().GetDeltaTime()),
		0
	);
}