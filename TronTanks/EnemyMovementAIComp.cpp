#include "EnemyMovementAIComp.h"

#include "GameTime.h"
#include "PhysicsEngine.h"
#include "Scene.h"

EnemyMovementAIComp::EnemyMovementAIComp(vic::GameObject* ownerPtr, VelocityMovementComponent* movComp)
	: BaseComponent{ownerPtr}
	  , m_MovComp{movComp}
	  , m_Direction{glm::vec2{0.f, 1.f}}
	  , m_ElapsedTime{0}
	  , m_RotationCooldown{2}, m_EnemySize{}
{
	m_ElapsedTime = m_RotationCooldown;
}

void EnemyMovementAIComp::OnSceneStart()
{
	m_EnemySize = Owner()->GetComponent<vic::OverlapComponent>()->GetDimensions();
}

void EnemyMovementAIComp::Update()
{
	m_MovComp->SetVelocity(m_Direction.x, m_Direction.y);
	m_ElapsedTime += static_cast<float>(vic::GameTime::GetInstance().GetDeltaTime());

	UpdateDirection();
}

bool EnemyMovementAIComp::CanMoveTo(const glm::vec2 dir)
{
	return !Owner()->GetScene()->GetPhysicsEngine().CollidesWithStatics(
		Owner()->GetTransform().Position() + m_EnemySize * dir
			, m_EnemySize 
	);
}

bool EnemyMovementAIComp::CanKeepMoveingTo(const glm::vec2 dir)
{
	glm::vec2 miniCollider(m_EnemySize / 10.f);

	if (!Owner()->GetScene()->GetPhysicsEngine().CollidesWithStatics(
		Owner()->GetTransform().Position() + m_EnemySize/2.f - (miniCollider / 2.f)
		+(( m_EnemySize/2.f) + (miniCollider / 2.f ))* dir
		, miniCollider))
		return true;

	return false;
}


void EnemyMovementAIComp::ChangeDir(glm::vec2 newDir)
{
	m_ElapsedTime = 0.f;
	m_Direction = newDir;
}
void EnemyMovementAIComp::UpdateDirection()
{
	bool needsToChangeDir{ !CanKeepMoveingTo(m_Direction)};

	if (m_ElapsedTime > m_RotationCooldown|| needsToChangeDir)
	{
		bool movingVertical{ abs(m_Direction.x) < FLT_EPSILON };

		if (movingVertical)
		{
			const bool canMoveLeft{ CanMoveTo(glm::vec2{-1, 0})};
			const bool canMoveRight{ CanMoveTo(glm::vec2{1, 0}) };
			if (canMoveLeft && canMoveRight)
			{
				const int randOption{ std::rand() % (3 - static_cast<int>(needsToChangeDir)) };

				if (randOption == 0)
					ChangeDir(glm::vec2{ -1, 0 });
				else if (randOption == 1)
					ChangeDir(glm::vec2{ 1, 0 });
			}
			else if (canMoveRight && 0 == std::rand() % (2 - static_cast<int>(needsToChangeDir)))
				ChangeDir(glm::vec2{ 1, 0 });
			else if (canMoveLeft && 0 == std::rand() % (2 - static_cast<int>(needsToChangeDir)))
				ChangeDir(glm::vec2{ -1, 0 });
		}
		else
		{
			const bool canMoveUp{ CanMoveTo(glm::vec2{0, -1})  };
			const bool canMoveDown{ CanMoveTo(glm::vec2{0, 1}) };
			if (canMoveUp && canMoveDown)
			{
				const int randOption{ std::rand() % (3 - static_cast<int>(needsToChangeDir))};

				if (randOption == 0)
					ChangeDir(glm::vec2{ 0,-1 });
				else if (randOption == 1)
					ChangeDir(glm::vec2{ 0, 1 });
			}
			else if (canMoveUp && 0 == std::rand() % (2 - static_cast<int>(needsToChangeDir)))
				ChangeDir(glm::vec2{ 0,-1 });
			else if (canMoveDown && 0 == std::rand() % (2 - static_cast<int>(needsToChangeDir)))
				ChangeDir(glm::vec2{ 0, 1 });
		}
	}
}