#include "PhysicsEngine.h"

#include <algorithm>
#include <array>
#include <stdexcept>

#include "GameTime.h"
#include "OverlapComponent.h"


using namespace vic;

void PhysicsEngine::CheckOverlaps()
{
	for (OverlapComponent* body : m_Bodies)
	{
		if(!body->HasOverlapBehaviour())
			continue;

		for (OverlapComponent* body2 : m_Bodies)
		{
			if(body == body2)
				continue;


			body->OverlapCheck(*body2);
		}
	}
}



void PhysicsEngine::RegisterColliderComp(ColliderComponent* bodyComponent)
{
	if (bodyComponent->m_staticObject)
		m_StaticColliders.push_back(bodyComponent);
	else
		m_DynamicColliders.push_back(bodyComponent);
}
void PhysicsEngine::UnregisterColliderComp(ColliderComponent* bodyComponent)
{
	if(bodyComponent->m_staticObject)
	{
		auto bodyIt = std::ranges::find(m_StaticColliders, bodyComponent);

		if (bodyIt == m_StaticColliders.end())
			throw std::runtime_error("unregistering unknown collider");

		m_StaticColliders.erase(bodyIt);
	}
	else
	{
		auto bodyIt = std::ranges::find(m_DynamicColliders, bodyComponent);

		if (bodyIt == m_DynamicColliders.end())
			throw std::runtime_error("unregistering unknown collider");

		m_DynamicColliders.erase(bodyIt);
	}
}

void PhysicsEngine::CheckColliders()
{
	const float fElapsedTime{ static_cast<float>(GameTime::GetInstance().GetDeltaTime()) };
	for (auto dyn : m_DynamicColliders)
	{
		Rectf dynRect{ dyn->m_GOTransformPtr->Position(), dyn->m_Dimensions };

		// Sort collisions in order of distance
		glm::vec2 cp, cn;
		float t = 0;
		std::vector<std::pair<int, float>> z;

		// Work out collision point, add it to vector along with rect ID
		for (size_t i = 0; i < m_StaticColliders.size(); i++)
		{
			Rectf staRect{ m_StaticColliders[i]->m_GOTransformPtr->Position(), m_StaticColliders[i]->m_Dimensions };
			if (DynamicRectVsRect(dynRect, *dyn->m_VelocityPtr, fElapsedTime, staRect, cp, cn, t))
			{
				z.push_back({ static_cast<int>(i), t });
			}
		}

		// Do the sort
		std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
		{
			return a.second < b.second;
		});

		// Now resolve the collision in correct order 
		for (auto& j : z)
		{
			Rectf staRect{m_StaticColliders[j.first]->m_GOTransformPtr->Position(), m_StaticColliders[j.first]->m_Dimensions};
			ResolveDynamicRectVsRect(dynRect, *dyn->m_VelocityPtr, fElapsedTime, staRect);
		}


		// UPdate the player rectangles position, with its modified velocity
		glm::vec2 moveVector{ fElapsedTime * dyn->m_VelocityPtr->x, fElapsedTime * dyn->m_VelocityPtr->y };
		dyn->m_GOTransformPtr->AddLocalPosition(moveVector.x, moveVector.y);
	}
}

void PhysicsEngine::RegisterOverlapComp(OverlapComponent* bodyComponent)
{
	m_Bodies.push_back(bodyComponent);
}
void PhysicsEngine::UnregisterOverlapComp(OverlapComponent* bodyComponent)
{
	auto bodyIt = std::ranges::find(m_Bodies, bodyComponent);

	if (bodyIt == m_Bodies.end())
		throw std::runtime_error("unregistering unknown Overlap");

	m_Bodies.erase(bodyIt);
}


bool PhysicsEngine::CollidesWithStatics(const glm::vec2& pos, const glm::vec2& size)
{
	for (auto& staticCollider : m_StaticColliders)
	{
		if (RectVsRect(pos, size, staticCollider->m_GOTransformPtr->Position(), staticCollider->m_Dimensions))
			return true;
	}

	return false;
}

bool PhysicsEngine::ResolveDynamicRectVsRect(const Rectf& dynamicRect, glm::vec2& dynamicRectVel, const float fixedTimeStep, const Rectf& staticRect)
{
	glm::vec2 contact_point, contact_normal;
	float contact_time = 0.0f;
	if (DynamicRectVsRect(dynamicRect, dynamicRectVel, fixedTimeStep, staticRect, contact_point, contact_normal, contact_time))
	{
		dynamicRectVel += contact_normal * glm::vec2(std::abs(dynamicRectVel.x), std::abs(dynamicRectVel.y)) * (1 - contact_time);
		return true;
	}

	return false;
}
bool PhysicsEngine::DynamicRectVsRect(const Rectf& dynamicRect, const glm::vec2& dynamicRectVel, const float fixedTimeStep, const Rectf& staticRect,
	glm::vec2& contactPoint, glm::vec2& contactNormal, float& contactTime)
{
	// Expand target rectangle by source dimensions
	Rectf expanded_target{};
	expanded_target.pos = staticRect.pos - glm::vec2{ dynamicRect.size.x / 2, dynamicRect.size.y / 2 };
	expanded_target.size = staticRect.size + dynamicRect.size;

	if (RayVsRect(dynamicRect.pos + glm::vec2{ dynamicRect.size.x / 2, dynamicRect.size.y / 2 }, dynamicRectVel * fixedTimeStep, &expanded_target, contactPoint, contactNormal, contactTime))
		return (contactTime >= 0.0f && contactTime < 1.0f);
	else
		return false;
}
bool PhysicsEngine::RayVsRect(const glm::vec2& rayOrigin, const glm::vec2& rayDir, const Rectf* target, glm::vec2& contactPoint,
	glm::vec2& contactNormal, float& tHitNear)
{
	contactNormal = { 0,0 };
	contactPoint = { 0,0 };

	// Cache division
	glm::vec2 invdir = 1.0f / rayDir;

	// Calculate intersections with rectangle bounding axes
	glm::vec2 tNear = (target->pos - rayOrigin) * invdir;
	glm::vec2 tFar = (target->pos + target->size - rayOrigin) * invdir;

	if (std::isnan(tFar.y) || std::isnan(tFar.x)) return false;
	if (std::isnan(tNear.y) || std::isnan(tNear.x)) return false;

	// Sort distances
	if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
	if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

	// Early rejection		
	if (tNear.x > tFar.y || tNear.y > tFar.x) return false;

	// Closest 'time' will be the first contact
	tHitNear = std::max(tNear.x, tNear.y);

	// Furthest 'time' is contact on opposite side of target
	float tHitFar = std::min(tFar.x, tFar.y);

	// Reject if ray direction is pointing away from object
	if (tHitFar < 0)
		return false;

	// Contact point of collision from parametric line equation
	contactPoint = rayOrigin + tHitNear * rayDir;

	if (tNear.x > tNear.y)
		if (invdir.x < 0)
			contactNormal = { 1, 0 };
		else
			contactNormal = { -1, 0 };
	else if (tNear.x < tNear.y)
		if (invdir.y < 0)
			contactNormal = { 0, 1 };
		else
			contactNormal = { 0, -1 };

	// Note if t_near == t_far, collision is principly in a diagonal
	// so pointless to resolve. By returning a CN={0,0} even though its
	// considered a hit, the resolver wont change anything.
	return true;
}


bool PhysicsEngine::PointVsRect(const glm::vec2& p, const Rectf& r)
{
	return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}
bool PhysicsEngine::RectVsRect(const Rectf& r1, const Rectf& r2)
{
	return RectVsRect(r1.pos, r1.size, r2.pos, r2.size);
}
bool PhysicsEngine::RectVsRect(const glm::vec2& pos1, const glm::vec2& dim1, const glm::vec2& pos2, const glm::vec2& dim2)
{
	//return (r1->pos.x < r2->pos.x + r2->size.x 
	//	&& r1->pos.x + r1->size.x > r2->pos.x 
	//	&& r1->pos.y < r2->pos.y + r2->size.y 
	//	&& r1->pos.y + r1->size.y > r2->pos.y);
	return (pos1.x < pos2.x + dim2.x 
		&& pos1.x + dim1.x > pos2.x 
		&& pos1.y < pos2.y + dim2.y 
		&& pos1.y + dim1.y > pos2.y);

}