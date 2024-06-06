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
	private:
		enum class PrimitiveType
		{
			rectangle,
			circle
		};

		bool m_Fill;

		PrimitiveType m_PrimitiveType;
		glm::vec2 m_Dimensions;
		SDL_Color m_Color;
	};
}
