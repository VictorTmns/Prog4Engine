#include "BulletLogicComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "PrimitivesRenderComponent.h"

BulletLogicComponent::BulletLogicComponent(vic::GameObject* ownerPtr, const glm::vec2& direction, int team)
	: BaseComponent{ownerPtr}, m_Direction{ direction }, m_Team{team}
{
}

void BulletLogicComponent::Update()
{
	Owner()->GetTransform().AddLocalPosition(
		m_Direction.x * m_Speed * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime()),
		m_Direction.y * m_Speed * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime())
	);
}

void BulletLogicComponent::BounceOutWall()
{
	if (m_NrOfBounces >= 5)
		Owner()->Destroy();

	m_NrOfBounces++;

	m_Direction *= -1;
	Owner()->GetTransform().AddLocalPosition(
		m_Direction.x * m_Speed * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime()),
		m_Direction.y * m_Speed * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime())
	);
}
