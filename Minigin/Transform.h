#pragma once
#include <glm/vec2.hpp>
#include <glm/ext/vector_float3.hpp>

#include "BaseComponent.h"

namespace vic
{
	class Transform final : public BaseComponent
	{
	private:
		struct TransformData
		{
			glm::vec2 pos{};
			double rot{};

			TransformData Multiply(const TransformData& other) const;
			TransformData operator-(const TransformData& other) const;
		};

	public:
		Transform(GameObject* owner)
			: BaseComponent{owner}
			{}

		//Getters
		const glm::vec2& Position() const;
		double Rotation() const;

		const glm::vec2& LocalPosition() const { return m_LocalTransform.pos; }
		double LocalRotation() const { return m_LocalTransform.rot; }

		//setters
		void SetLocalPosition(const float x, const float y);
		void AddLocalPosition(const float x, const float y);
		void SetLocalRotation(double rotation);
		void AddLocalRotation(double rotation);

		void SetNewParent(GameObject* newParentPtr, bool keepWorldPosition);


	private:
		Transform* m_OwnerTransform{};

		mutable bool m_WorldTransformDirty{ true };
		mutable TransformData m_WorldTransform{};
		TransformData m_LocalTransform{};

	private:
		void CleanTransform() const;
		void SetTransformDirty() const;
		TransformData CalculateWorldTransform() const;
	};
}
