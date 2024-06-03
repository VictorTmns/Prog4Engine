#include "FPSComponent.h"

#include <iomanip>
#include <sstream>

#include "GameObject.h"
#include "ResourceManager.h"
#include "GameTime.h"


vic::FPSComponent::FPSComponent(GameObject* owner, Font* font)
	: BaseComponent{owner}
	, m_delay{0}
	, m_count{0}
	, m_maxDelay{.3}
{
	m_TextRenderer = owner->AddComponent<TextRenderComponent>(font);
}

void vic::FPSComponent::Update()
{
	m_delay += GameTime::GetInstance().GetDeltaTime();
	m_count++;
	if (m_delay >= m_maxDelay)
	{
		m_TextRenderer->SetText(std::format("{:.1f}", m_count / m_delay));
		m_delay = 0;
		m_count = 0;
	}
}

std::string vic::FPSComponent::floatToString(float value) const
{
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(2) << value;
	return stream.str();
}