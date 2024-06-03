#pragma once
#include "BaseComponent.h"

class KeyboardTestComponent final : public vic::BaseComponent
{
public:
	KeyboardTestComponent(vic::GameObject* owner);

	void Move(float x, float y);
private:
	float m_Speed;
};
