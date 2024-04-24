#include "CircleRenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"

CircleRenderComponent::CircleRenderComponent(minigin::GameObject* owner, float radius, SDL_Color color)
	: BaseComponent{owner}
	, m_Radius{radius}
	, m_Color{ color }
{
}

void CircleRenderComponent::Render() const
{
	const glm::vec2 pos = GetOwner()->GetWorldTransform().GetPosition();

	SDL_SetRenderDrawColor(minigin::Renderer::GetInstance().GetSDLRenderer(),
		0, 0, 255, 255);
	minigin::Renderer::GetInstance().FillCircle(pos.x, pos.y, m_Radius, m_Color);

}
