#include "OrbitComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"

minigin::OrbitComponent::OrbitComponent(GameObject* ownerPtr, float orbitingSpeed)
	: BaseComponent{ownerPtr}
	, m_OrbitingSpeed{ orbitingSpeed }
{
	
}


void minigin::OrbitComponent::Update()
{
	GetOwner()->AddLocalRotation(m_OrbitingSpeed * Time::GetInstance().GetDeltaTime());
}
