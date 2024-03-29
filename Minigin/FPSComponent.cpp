﻿#include "FPSComponent.h"

#include <iomanip>
#include <sstream>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"


minigin::FPSComponent::FPSComponent(GameObject* owner, Font* font)
	: BaseComponent{owner}
	, m_delay{0}
	, m_count{0}
	, m_maxDelay{.3}
{
	m_TextRenderer = owner->AddComponent<TextRenderComponent>(font);
}

void minigin::FPSComponent::Update()
{
	m_delay += Time::GetInstance().GetDeltaTime();
	m_count++;
	if (m_delay >= m_maxDelay)
	{
		m_TextRenderer->SetText(std::format("{:.1f}", m_count / m_delay));
		m_delay = 0;
		m_count = 0;
	}
}

std::string minigin::FPSComponent::floatToString(float value) const
{
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(2) << value;
	return stream.str();
}