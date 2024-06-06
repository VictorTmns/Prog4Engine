#include "PrimitivesRenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"

using namespace vic;
PrimitivesRenderComponent::PrimitivesRenderComponent(GameObject* owner, float radius, SDL_Color color)
	: BaseComponent{owner}
	, m_Dimensions{radius}
	, m_Color{ color }
{
}

PrimitivesRenderComponent::PrimitivesRenderComponent(GameObject* owner, PrimitiveType primitiveType,
	const glm::vec2& dimensions, SDL_Color color)
{
}

void PrimitivesRenderComponent::Render(const Renderer* renderer) const
{
	const glm::vec2 pos = Owner()->GetTransform().Position();

	renderer->SetDrawColor(0, 0, 255, 0);
	renderer->FillOval(pos.x, pos.y, m_Radius, m_Color);

}
