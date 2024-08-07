#include "Transform.h"

#include <cmath>
#include <SDL_stdinc.h>
#include <glm/gtx/rotate_vector.hpp>

#include "GameObject.h"


//===========================================
//===============setters=====================
//===========================================
void vic::Transform::SetLocalPosition(const float x, const float y)
{
	m_LocalTransform.pos.x = x;
	m_LocalTransform.pos.y = y;

	SetTransformDirty();
}


void vic::Transform::AddLocalPosition(const float x, const float y)
{
	m_LocalTransform.pos.x += x;
	m_LocalTransform.pos.y += y;

	SetTransformDirty();
}

void vic::Transform::SetLocalRotation(const float rotation)
{
	m_LocalTransform.rot = static_cast<float>(std::fmod(rotation, 360.0));
	if (m_LocalTransform.rot < 0.0)
		m_LocalTransform.rot += 360.0;

	SetTransformDirty();
}


void vic::Transform::AddLocalRotation(const float rotation)
{
	m_LocalTransform.rot = static_cast<float>(std::fmod(m_LocalTransform.rot + rotation, 360.0));
	if (m_LocalTransform.rot < 0.0)
		m_LocalTransform.rot += 360.0;

	SetTransformDirty();
}


void vic::Transform::SetWorldPosition(const float x, const float y)
{
	m_LocalTransform.pos.x = m_WorldTransform.pos.x - m_LocalTransform.pos.x + x;
	m_LocalTransform.pos.y = m_WorldTransform.pos.y - m_LocalTransform.pos.y + y;

	SetTransformDirty();
}
void vic::Transform::SetWorldRotation(const float rotation)
{
	m_LocalTransform.rot = static_cast<float>(std::fmod(m_WorldTransform.rot - m_LocalTransform.rot + rotation, 360.0));
	if (m_LocalTransform.rot < 0.0)
		m_LocalTransform.rot += 360.0;

	SetTransformDirty();
}


void vic::Transform::SetNewParent(GameObject* newParentPtr, bool keepWorldPosition)
{
	m_OwnerTransform = &newParentPtr->GetTransform();

	if (keepWorldPosition)
	{
		//make sure the transformData is clean
		CleanTransform();
		m_OwnerTransform->CleanTransform();

		//set the local transformData to the difference to between the parent-worldTransformData
		//and the old worldTransformData
		m_LocalTransform = m_WorldTransform - m_OwnerTransform->m_WorldTransform;
	}
	else
		SetTransformDirty();
}







//===========================================
//===============Getters=====================
//===========================================

const glm::vec2& vic::Transform::Position() const
{
	CleanTransform();
	return m_WorldTransform.pos;
}

float vic::Transform::Rotation() const
{
	CleanTransform();
	return m_WorldTransform.rot;
}

void vic::Transform::CleanTransform() const
{
	if (m_WorldTransformDirty)
	{
		m_WorldTransform = CalculateWorldTransform();
		m_WorldTransformDirty = false;
	}
}



void vic::Transform::SetTransformDirty() const
{
	m_WorldTransformDirty = true;

	for (int i{0}; i < Owner()->GetChildCount(); i++)
	{
		Owner()->GetChildAt(i)->GetTransform().SetTransformDirty();
	}
}

//===========================================
//===================Misc====================
//===========================================

vic::Transform::TransformData vic::Transform::CalculateWorldTransform() const
{
	if (m_OwnerTransform == nullptr)
		return m_LocalTransform;

	return m_LocalTransform.Multiply(m_OwnerTransform->CalculateWorldTransform());
}

vic::Transform::TransformData vic::Transform::TransformData::Multiply(const TransformData& other) const
{
	TransformData result{};

	result.pos = other.pos + glm::rotate(pos, other.rot);

	return result;
}

vic::Transform::TransformData vic::Transform::TransformData::operator-(const TransformData& other) const
{
	TransformData result{};
	result.pos = pos - other.pos;
	return result;
}
