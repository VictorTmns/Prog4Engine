#pragma once
#include "BarrelComponent.h"
#include "BarrelComponent.h"
#include "BarrelComponent.h"
#include "BaseComponent.h"
#include "VelocityMovementComponent.h"

class EnemyAIComp : public vic::BaseComponent
{
public:
	EnemyAIComp(vic::GameObject* ownerPtr, VelocityMovementComponent* movComp, BarrelComponent* barrelComp);

	void OnStart() override;

	void Update() override;
	void Hit();
private:
	bool CanMoveTo(const glm::vec2 dir);
	bool CanKeepMoveingTo(const glm::vec2 dir);

	void ChangeDir(glm::vec2 newDir);
	void UpdateDirection();

private:
	VelocityMovementComponent* m_MovComp;
	BarrelComponent* m_BarrelComp;

	glm::vec2 m_Direction;
	float m_ElapsedTime;
	const float m_RotationCooldown = 2.f;

	glm::vec2 m_EnemySize;

	int m_LivesLeft;
};
