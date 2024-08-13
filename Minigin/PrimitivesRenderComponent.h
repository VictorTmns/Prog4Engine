#pragma once
#include <SDL_pixels.h>

#include "BaseComponent.h"
#include "ControllerManager.h"
#include "glm/glm.hpp"

namespace vic
{
	class PrimitivesRenderComponent : public BaseComponent
	{
	public:
		PrimitivesRenderComponent(GameObject* owner, const glm::vec2& rectDimensions, SDL_Color color, bool fill = true);
		PrimitivesRenderComponent(GameObject* owner, float radius, SDL_Color color, bool fill = true);

		void Render(const Renderer* renderer) const override;

		void SetRectDimensions(const glm::vec2& rectDimensions) { m_Dimensions = rectDimensions; }
		void SetCircleRadius(float radius) { m_Dimensions.s = radius; }
		void SetOffset(const glm::vec2& offset) { m_Offset = offset; }
		void SetColor(SDL_Color color) { m_Color = color; }
	private:
		enum class PrimitiveType
		{
			rectangle,
			circle
		};

		bool m_Fill;

		PrimitiveType m_PrimitiveType;
		glm::vec2 m_Offset = { 0.f, 0.f };
		glm::vec2 m_Dimensions = {0.f, 0.f};
		SDL_Color m_Color;
	};
}
