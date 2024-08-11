#include "PhysicsEngine.h"

#include <algorithm>
#include <array>
#include <stdexcept>

#include "GameTime.h"
#include "OverlapComponent.h"

using namespace vic;

namespace aabb
{
	bool PointVsRect(const glm::vec2& p, const PhysicsEngine::Rectf* r)
	{
		return (p.x >= r->pos.x && p.y >= r->pos.y && p.x < r->pos.x + r->size.x && p.y < r->pos.y + r->size.y);
	}

	bool RectVsRect(const PhysicsEngine::Rectf* r1, const PhysicsEngine::Rectf* r2)
	{
		return (r1->pos.x < r2->pos.x + r2->size.x && r1->pos.x + r1->size.x > r2->pos.x && r1->pos.y < r2->pos.y + r2->size.y && r1->pos.y + r1->size.y > r2->pos.y);
	}

	bool RayVsRect(const glm::vec2& ray_origin, const glm::vec2& ray_dir, const PhysicsEngine::Rectf* target, glm::vec2& contact_point, glm::vec2& contact_normal, float& t_hit_near)
	{
		contact_normal = { 0,0 };
		contact_point = { 0,0 };

		// Cache division
		glm::vec2 invdir = 1.0f / ray_dir;

		// Calculate intersections with rectangle bounding axes
		glm::vec2 t_near = (target->pos - ray_origin) * invdir;
		glm::vec2 t_far = (target->pos + target->size - ray_origin) * invdir;

		if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
		if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

		// Sort distances
		if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
		if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

		// Early rejection		
		if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

		// Closest 'time' will be the first contact
		t_hit_near = std::max(t_near.x, t_near.y);

		// Furthest 'time' is contact on opposite side of target
		float t_hit_far = std::min(t_far.x, t_far.y);

		// Reject if ray direction is pointing away from object
		if (t_hit_far < 0)
			return false;

		// Contact point of collision from parametric line equation
		contact_point = ray_origin + t_hit_near * ray_dir;

		if (t_near.x > t_near.y)
			if (invdir.x < 0)
				contact_normal = { 1, 0 };
			else
				contact_normal = { -1, 0 };
		else if (t_near.x < t_near.y)
			if (invdir.y < 0)
				contact_normal = { 0, 1 };
			else
				contact_normal = { 0, -1 };

		// Note if t_near == t_far, collision is principly in a diagonal
		// so pointless to resolve. By returning a CN={0,0} even though its
		// considered a hit, the resolver wont change anything.
		return true;
	}

	bool DynamicRectVsRect(const PhysicsEngine::Rectf* dynamicRect, const glm::vec2& dynamicRectVel, const float fTimeStep, const PhysicsEngine::Rectf& r_static,
		glm::vec2& contact_point, glm::vec2& contact_normal, float& contact_time)
	{
		// Expand target rectangle by source dimensions
		PhysicsEngine::Rectf expanded_target;
		expanded_target.pos = r_static.pos - glm::vec2{ dynamicRect->size.x / 2, dynamicRect->size.y / 2 };
		expanded_target.size = r_static.size + dynamicRect->size;

		if (RayVsRect(dynamicRect->pos + glm::vec2{ dynamicRect->size.x / 2, dynamicRect->size.y / 2 }, dynamicRectVel * fTimeStep, &expanded_target, contact_point, contact_normal, contact_time))
			return (contact_time >= 0.0f && contact_time < 1.0f);
		else
			return false;
	}



	bool ResolveDynamicRectVsRect(PhysicsEngine::Rectf* r_dynamic, glm::vec2& dynamicRectVel, const float fTimeStep, PhysicsEngine::Rectf* r_static)
	{
		glm::vec2 contact_point, contact_normal;
		float contact_time = 0.0f;
		if (DynamicRectVsRect(r_dynamic, dynamicRectVel, fTimeStep, *r_static, contact_point, contact_normal, contact_time))
		{
			dynamicRectVel += contact_normal * glm::vec2(std::abs(dynamicRectVel.x), std::abs(dynamicRectVel.y)) * (1 - contact_time);
			return true;
		}

		return false;
	}
}




void PhysicsEngine::CheckOverlaps()
{
	for (OverlapComponent* body : m_Bodies)
	{
		if(!body->m_HasOverlapBehavior)
			continue;

		for (OverlapComponent* body2 : m_Bodies)
		{
			if(body == body2)
				continue;


			if (!IsOverlapping(
				body->m_GOTransformPtr->Position() + body->m_Offset, body2->m_GOTransformPtr->Position() + body2->m_Offset, 
				body->m_Dimensions, body2->m_Dimensions)
				)
				continue;


			body->m_CollisionFunc(body, body2);
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
			if (aabb::DynamicRectVsRect(&dynRect, *dyn->m_VelocityPtr, fElapsedTime, staRect, cp, cn, t))
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
		for (auto j : z)
		{
			Rectf staRect{m_StaticColliders[j.first]->m_GOTransformPtr->Position(), m_StaticColliders[j.first]->m_Dimensions};
			aabb::ResolveDynamicRectVsRect(&dynRect, *dyn->m_VelocityPtr, fElapsedTime, &staRect);
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

bool PhysicsEngine::IsOverlapping(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec2& dim1,
	const glm::vec2 dim2)
{
	return (
		   pos1.x			< (pos2.x + dim2.x)
		&& (pos1.x + dim1.x) > pos2.x
		&& (pos1.y + dim1.y) > pos2.y
		&& pos1.y			< (pos2.y + dim2.y)
		);
}



