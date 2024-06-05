#include "OrbitComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameTime.h"

OrbitComponent::OrbitComponent(vic::GameObject* ownerPtr, float orbitingSpeed)
	: BaseComponent{ownerPtr}
	, m_OrbitingSpeed{ orbitingSpeed }
{
	
}


void OrbitComponent::Update()
{
	Owner()->GetTransform().AddLocalRotation(m_OrbitingSpeed * static_cast<float>(GameTime::GetInstance().GetDeltaTime()));
}
