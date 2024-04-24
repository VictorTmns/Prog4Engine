#include "OrbitComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameTime.h"

minigin::OrbitComponent::OrbitComponent(GameObject* ownerPtr, float orbitingSpeed)
	: BaseComponent{ownerPtr}
	, m_OrbitingSpeed{ orbitingSpeed }
{
	
}


void minigin::OrbitComponent::Update()
{
	GetOwner()->AddLocalRotation(m_OrbitingSpeed * GameTime::GetInstance().GetDeltaTime());
}
