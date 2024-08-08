#include "BulletLogicComponent.h"

#include "GameObject.h"
#include "PrimitivesRenderComponent.h"

BulletLogicComponent::BulletLogicComponent(vic::GameObject* ownerPtr, const glm::vec2& startPos, const glm::vec2& direction)
	: BaseComponent{ownerPtr}, m_Direction{}
{
	ownerPtr->AddComponent<vic::PrimitivesRenderComponent>(5.f, SDL_Color{0, 0, 255, 0});

	Owner()->GetTransform().SetWorldPosition(startPos.x, startPos.y);
	m_Direction = direction;

}

void BulletLogicComponent::Update()
{
	Owner()->GetTransform().AddLocalPosition(m_Direction.x * m_Speed, m_Direction.y * m_Speed);
}
