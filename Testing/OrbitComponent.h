#pragma once
#include "BaseComponent.h"

namespace minigin
{
	class OrbitComponent final :public BaseComponent
	{
	public:
		OrbitComponent(GameObject* ownerPtr, float orbitingSpeed);

		void Update() override;
	private:
		float m_OrbitingSpeed;
	};
}


