#pragma once
#include <glm/vec2.hpp>
#include <glm/ext/vector_float3.hpp>

namespace minigin
{
	class Transform final
	{
	public:
		Transform(glm::vec2	translation = {}, double rotation = 0.0)
			: m_Translation{translation.x, translation.y}, m_Rotation{rotation} {}
		Transform(float x, float y, double rotation)
			: m_Translation{ x, y}, m_Rotation{ rotation } {}

		//Getters
		const glm::vec2& GetPosition() const { return m_Translation; }
		double GetRotation() const { return m_Rotation; }

		//setters
		void SetPosition(const float x, const float y);
		void AddPosition(const float x, const float y);

		void SetRotation(double rotation);
		void AddRotation(double rotation);

		Transform operator+(const Transform& other) const;
		Transform operator-(const Transform& other) const;
		minigin::Transform Multiply(const Transform& other, bool inheritRotation = true) const;

	private:
		glm::vec2 m_Translation{};
		double m_Rotation{};
	};
}
