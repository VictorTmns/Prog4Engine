#pragma once
#include "BaseComponent.h"

class KeyboardTestComponent final : public minigin::BaseComponent
{
public:
	KeyboardTestComponent(minigin::GameObject* owner);

	void Move(float x, float y);
private:
	float m_Speed;
};
