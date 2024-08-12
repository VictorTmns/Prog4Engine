#pragma once
#include <memory>

#include "ColliderComponent.h"
#include "OverlapComponent.h"



namespace vic
{
	class PhysicsEngine final
	{
	public:
		struct Rectf
		{
			glm::vec2 pos;
			glm::vec2 size;
		};

		PhysicsEngine() = default;
		~PhysicsEngine() = default;

		void RegisterOverlapComp(OverlapComponent* bodyComponent);
		void UnregisterOverlapComp(OverlapComponent* bodyComponent);
		void CheckOverlaps();

		void RegisterColliderComp(ColliderComponent* bodyComponent);
		void UnregisterColliderComp(ColliderComponent* bodyComponent);
		void CheckColliders();


		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;


		bool CollidesWithStatics(const glm::vec2& pos, const glm::vec2& size);


		static bool ResolveDynamicRectVsRect(const Rectf& dynamicRect, glm::vec2& dynamicRectVel, const float fixedTimeStep, const Rectf& staticRect);
		static bool DynamicRectVsRect(const Rectf& dynamicRect, const glm::vec2& dynamicRectVel, const float fixedTimeStep, const Rectf& staticRect,
		                              glm::vec2& contactPoint, glm::vec2& contactNormal, float& contactTime);
		static bool RayVsRect(const glm::vec2& rayOrigin, const glm::vec2& rayDir, const Rectf* target, glm::vec2& contactPoint, glm::vec2& contactNormal, float& tHitNear);
		static bool PointVsRect(const glm::vec2& p, const Rectf& r);
		static bool RectVsRect(const Rectf& r1, const Rectf& r2);
		static bool RectVsRect(const glm::vec2& pos1, const glm::vec2& dim1, const glm::vec2& pos2, const glm::vec2& dim2);

	private:
		std::vector<OverlapComponent*> m_Bodies;
		std::vector<ColliderComponent*> m_DynamicColliders;
		std::vector<ColliderComponent*> m_StaticColliders;

		static bool IsOverlapping(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec2& dim1, const glm::vec2 dim2);
	};
}
