#pragma once
#include <SDL_pixels.h>

#include "BaseComponent.h"
#include "ControllerManager.h"

class CircleRenderComponent : public minigin::BaseComponent
{
public:
	CircleRenderComponent(minigin::GameObject* owner ,float radius, SDL_Color color);

	void Render(const minigin::Renderer* renderer) const override;
private:
	float m_Radius;
	SDL_Color m_Color;
};