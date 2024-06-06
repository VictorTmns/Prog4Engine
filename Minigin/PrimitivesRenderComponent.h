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
		enum PrimitiveType
		{
			rectangle,
			oval
		};

		PrimitivesRenderComponent(GameObject* owner, PrimitiveType primitiveType, const glm::vec2& dimensions, SDL_Color color);

		void Render(const Renderer* renderer) const override;
	private:
		PrimitiveType m_Primitive;
		glm::vec2 m_Dimensions;
		SDL_Color m_Color;
	};
}
