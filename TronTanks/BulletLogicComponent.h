#pragma once
#include <glm/glm.hpp>

#include "BaseComponent.h"

class BulletLogicComponent : public vic::BaseComponent
{
public:
	BulletLogicComponent(vic::GameObject* ownerPtr, const glm::vec2& direction);

	void Update() override;
	void BounceOutWall(const glm::vec2& wallPos, const glm::vec2& wallDimensions);

private:
	void MoveOutOfWall(const glm::vec2& wallPos, const glm::vec2& wallDimensions);
private:
	const float m_Speed{500.f};
	glm::vec2 m_Direction;

	int m_NrOfBounces{0};
};
