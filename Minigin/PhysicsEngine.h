#pragma once
#include <memory>

#include "ColliderComponent.h"
#include "OverlapComponent.h"



namespace vic
{
	class PhysicsEngine final
	{
	public:
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

		struct HitInfo
		{
			float lambda;
			glm::vec2 intersectPoint;
			glm::vec2 normal;
		};

		struct Rectf
		{
			glm::vec2 pos;
			glm::vec2 size;
		};

		bool Raycast(const glm::vec2* vertices, const size_t nrVertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);

	private:
		std::vector<OverlapComponent*> m_Bodies;
		std::vector<ColliderComponent*> m_DynamicColliders;
		std::vector<ColliderComponent*> m_StaticColliders;

		static bool IsOverlapping(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec2& dim1, const glm::vec2 dim2);
	};
}
