#pragma once
#include <glm/glm.hpp>

#include "BaseComponent.h"

class BulletLogicComponent : public vic::BaseComponent
{
public:
	BulletLogicComponent(vic::GameObject* ownerPtr, const glm::vec2& direction, int team);

	void Update() override;
	void BounceOutWall();
	int GetBulletTeam() { return m_Team; }

private:
	const float m_Speed{500.f};
	glm::vec2 m_Direction;
	int m_Team;

	int m_NrOfBounces{0};
};
