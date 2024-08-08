#include "BulletLogicComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "PrimitivesRenderComponent.h"

BulletLogicComponent::BulletLogicComponent(vic::GameObject* ownerPtr, const glm::vec2& direction)
	: BaseComponent{ownerPtr}, m_Direction{ direction }
{
}

void BulletLogicComponent::Update()
{
	Owner()->GetTransform().AddLocalPosition(
		m_Direction.x * m_Speed * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime()),
		m_Direction.y * m_Speed * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime())
	);
}
