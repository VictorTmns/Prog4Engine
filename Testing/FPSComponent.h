#pragma once
#include <memory>

#include "BaseComponent.h"
#include "TextRenderComponent.h"
#include "GameTime.h"

namespace minigin
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(GameObject* owner, Font* font);
		void Update() override;
	
	private:
		std::string floatToString(float value) const;
	
	
		TextRenderComponent* m_TextRenderer;
		double m_delay;
		int m_count;
		const double m_maxDelay;
	};
}
