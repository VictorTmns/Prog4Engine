#pragma once
#include "BaseComponent.h"


class OrbitComponent final :public minigin::BaseComponent
{
public:
	OrbitComponent(minigin::GameObject* ownerPtr, float orbitingSpeed);

	void Update() override;
private:
	float m_OrbitingSpeed;
};



