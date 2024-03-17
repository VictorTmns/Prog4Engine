#include "Transform.h"

#include <cmath>
#include <SDL_stdinc.h>
#include <glm/gtx/rotate_vector.hpp>

void minigin::Transform::SetPosition(const float x, const float y)
{
	m_Translation.x = x;
	m_Translation.y = y;
}

void minigin::Transform::AddPosition(const float x, const float y)
{
	m_Translation.x += x;
	m_Translation.y += y;
}

void minigin::Transform::SetRotation(const double rotation)
{
	m_Rotation = fmod(rotation, 360.0);
	if (m_Rotation < 0.0)
		m_Rotation += 360.0;
}

void minigin::Transform::AddRotation(const double rotation)
{
	m_Rotation = fmod(m_Rotation + rotation, 360.0);
	if (m_Rotation < 0.0)
		m_Rotation += 360.0;
}

minigin::Transform minigin::Transform::operator+(const Transform& other) const
{
	Transform result;

	result.m_Translation = m_Translation + other.m_Translation;
	result.m_Rotation = m_Rotation + other.m_Rotation;

	return result;
}


minigin::Transform minigin::Transform::operator-(const Transform& other) const
{
	Transform result;

	result.m_Translation = m_Translation - other.m_Translation;
	result.m_Rotation = m_Rotation - other.m_Rotation;

	return result;
}



minigin::Transform minigin::Transform::Multiply(const Transform& other, bool inheritRotation) const
{
	Transform result{};

	float otherRotation{};
	if (inheritRotation)
		otherRotation = static_cast<float>(other.m_Rotation);


	result = other.m_Translation + glm::rotate(m_Translation, otherRotation);
	result.m_Rotation = m_Rotation + otherRotation;


	return result;
}
