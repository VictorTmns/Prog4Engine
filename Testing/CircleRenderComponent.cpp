#include "CircleRenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"

CircleRenderComponent::CircleRenderComponent(vic::GameObject* owner, float radius, SDL_Color color)
	: BaseComponent{owner}
	, m_Radius{radius}
	, m_Color{ color }
{
}

void CircleRenderComponent::Render(const vic::Renderer* renderer) const
{
	const glm::vec2 pos = GetOwner()->GetWorldTransform().GetPosition();

	renderer->SetDrawColor(0, 0, 255, 0);
	renderer->FillCircle(pos.x, pos.y, m_Radius, m_Color);

}
