#include "KeyboardTestComponent.h"

#include "GameObject.h"
#include "GameTime.h"

KeyboardTestComponent::KeyboardTestComponent(vic::GameObject* owner)
	: BaseComponent{owner}
	, m_Speed{80.f}
{
}

void KeyboardTestComponent::Move(float x, float y)
{
	Owner()->GetTransform().AddLocalPosition(
		x * m_Speed * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime()),
		y * m_Speed * static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime())
	);
}
