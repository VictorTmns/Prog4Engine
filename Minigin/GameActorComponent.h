#pragma once
#include "BaseComponent.h"

class GameActorComponent final : public minigin::BaseComponent
{
public:
	GameActorComponent(minigin::GameObject* owner);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Move(float x, float y);
	float m_Speed;
};
