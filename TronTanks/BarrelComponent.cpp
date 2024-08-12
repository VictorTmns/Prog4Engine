#include "BarrelComponent.h"

#include "CreateBullet.h"
#include "PrimitivesRenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"

BarrelComponent::BarrelComponent(vic::GameObject* ownerPtr)
	: BaseComponent{ownerPtr}
	, m_BarrelDirection{ Direction::down }
{
	m_BarrelRenderer = ownerPtr->AddComponent<vic::PrimitivesRenderComponent>(
		glm::vec2{}, SDL_Color{ 0, 255, 0, 255 });
	ReloadBarrelRenderer();



	
}

void BarrelComponent::Shoot(Direction direction, int team)
{
	m_BarrelDirection = direction;
	ReloadBarrelRenderer();

	CreateBullet(Owner()->GetScene(), Owner()->GetTransform().Position(), DirectionToVec(m_BarrelDirection), team);
}

void BarrelComponent::ReloadBarrelRenderer()
{
	constexpr float barrelLength{25.f};
	constexpr float barrelWidth{5.f};
	switch (m_BarrelDirection)
	{
	case Direction::up:
		m_BarrelRenderer->SetOffset({ -(barrelWidth / 2), -barrelLength });
		m_BarrelRenderer->SetRectDimensions(glm::vec2{ barrelWidth, barrelLength });
		break;
	case Direction::down:
		m_BarrelRenderer->SetOffset({ -(barrelWidth / 2), 0.f });
		m_BarrelRenderer->SetRectDimensions(glm::vec2{ barrelWidth, barrelLength });
		break;
	case Direction::left:
		m_BarrelRenderer->SetOffset({ -barrelLength, -(barrelWidth / 2) });
		m_BarrelRenderer->SetRectDimensions(glm::vec2{ barrelLength, barrelWidth });
		break;
	case Direction::right:
		m_BarrelRenderer->SetOffset({ 0.f, -(barrelWidth / 2) });
		m_BarrelRenderer->SetRectDimensions(glm::vec2{ barrelLength, barrelWidth });
		break;
	default: ;
	}
}

glm::vec2 BarrelComponent::DirectionToVec(Direction dir)
{
	switch (dir)
	{
	case Direction::up:
		return glm::vec2{ 0, -1 };
	case Direction::down:
		return glm::vec2{ 0, 1 };
	case Direction::left:
		return glm::vec2{ -1, 0 };
	case Direction::right:
		return glm::vec2{ 1, 0 };
	}
	return {};
}
