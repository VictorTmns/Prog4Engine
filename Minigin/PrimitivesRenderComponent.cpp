#include "PrimitivesRenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"

using namespace vic;

PrimitivesRenderComponent::PrimitivesRenderComponent(GameObject* owner, const glm::vec2& rectDimensions,
	SDL_Color color, bool fill)
	: BaseComponent{ owner }
	, m_PrimitiveType{PrimitiveType::rectangle }
	, m_Dimensions{rectDimensions}
	, m_Color{color}
	, m_Fill{fill}
{
}

PrimitivesRenderComponent::PrimitivesRenderComponent(GameObject* owner, float radius, SDL_Color color, bool fill)
	: BaseComponent{owner}
	, m_PrimitiveType{PrimitiveType::circle}
	, m_Dimensions{radius}
	, m_Color{color}
	, m_Fill{ fill }
{
}


void PrimitivesRenderComponent::Render(const Renderer* renderer) const
{
	const glm::vec2 pos = Owner()->GetTransform().Position() + m_Offset;

	renderer->SetDrawColor(m_Color.r, m_Color.g, m_Color.b, m_Color.a);

	switch (m_PrimitiveType)
	{
	case PrimitiveType::rectangle:
		if (m_Fill)
			renderer->FillRect(pos.x, pos.y, m_Dimensions.x, m_Dimensions.y, m_Color);
		else
			renderer->RenderRect(pos.x, pos.y, m_Dimensions.x, m_Dimensions.y, m_Color);

		break;
	case PrimitiveType::circle:
		if (m_Fill)
			renderer->FillCircle(pos.x, pos.y, m_Dimensions.s, m_Color);
		else
			renderer->RenderCircle(pos.x, pos.y, m_Dimensions.s, m_Color);
		break;
	}

}
