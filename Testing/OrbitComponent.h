#pragma once
#include "BaseComponent.h"


class OrbitComponent final :public vic::BaseComponent
{
public:
	OrbitComponent(vic::GameObject* ownerPtr, float orbitingSpeed);

	void Update() override;
private:
	float m_OrbitingSpeed;
};



