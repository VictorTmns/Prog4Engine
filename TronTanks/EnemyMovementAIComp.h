#pragma once
#include "BarrelComponent.h"
#include "BarrelComponent.h"
#include "BarrelComponent.h"
#include "BaseComponent.h"
#include "VelocityMovementComponent.h"

class EnemyMovementAIComp : public vic::BaseComponent
{
public:
	EnemyMovementAIComp(vic::GameObject* ownerPtr, VelocityMovementComponent* movComp);

	void OnSceneStart() override;

	void Update() override;
private:
	bool CanMoveTo(const glm::vec2 dir);
	bool CanKeepMoveingTo(const glm::vec2 dir);

	void ChangeDir(glm::vec2 newDir);
	void UpdateDirection();

private:
	VelocityMovementComponent* m_MovComp;

	glm::vec2 m_Direction;
	float m_ElapsedTime;
	const float m_RotationCooldown;

	glm::vec2 m_EnemySize;

	int m_LivesLeft;
};
