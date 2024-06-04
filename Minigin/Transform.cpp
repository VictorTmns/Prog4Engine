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

void vic::Transform::SetLocalRotation(const double rotation)
{
	m_LocalTransform.rot = std::fmod(rotation, 360.0);
	if (m_LocalTransform.rot < 0.0)
		m_LocalTransform.rot += 360.0;

	SetTransformDirty();
}

void vic::Transform::AddLocalRotation(const double rotation)
{
	m_LocalTransform.rot = std::fmod(m_LocalTransform.rot + rotation, 360.0);
	if (m_LocalTransform.rot < 0.0)
		m_LocalTransform.rot += 360.0;

	SetTransformDirty();
}

void vic::Transform::SetNewParent(GameObject* newParentPtr, bool keepWorldPosition)
{
	m_OwnerTransform = &newParentPtr->GetTransform();

	if (keepWorldPosition)
	{
		//make sure the transforms are clean
		CleanTransform();
		m_OwnerTransform->CleanTransform();

		//set the local transform to the difference to between the parent-worldTransform
		//and the old worldTransform
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

double vic::Transform::Rotation() const
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

	for (int i{0}; i < GetOwner()->GetChildCount(); i++)
	{
		GetOwner()->GetChildAt(i)->GetTransform().SetTransformDirty();
	}
}

//===========================================
//===================Misc====================
//===========================================

vic::Transform::namePlease vic::Transform::CalculateWorldTransform() const
{
	if (m_OwnerTransform == nullptr)
		return m_LocalTransform;

	return m_LocalTransform.Multiply(m_OwnerTransform->CalculateWorldTransform());
}

vic::Transform::namePlease vic::Transform::namePlease::Multiply(const namePlease& other) const
{
	namePlease result{};

	result.pos = other.pos + glm::rotate(pos, static_cast<float>(other.rot));

	return result;
}

vic::Transform::namePlease vic::Transform::namePlease::operator-(const namePlease& other) const
{
	namePlease result{};
	result.pos = pos - other.pos;
	return result;
}
