#pragma once
#include <vector>

#include "BaseComponent.h"



class ThrashTheCacheComponent final : public minigin::BaseComponent
{
public:
	ThrashTheCacheComponent(minigin::GameObject* parentPtr);
	void Update() override;
private:
	void Calculate3DGameobjectData();
	void CalculateAlt3DGameobjectData();
	struct transform
	{
		float matrix[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		};
	};

	class GameObject3D
	{
	public:
		transform local;
		int id = 0;
	};
	class GameObject3DAlt
	{
	public:
		transform* local;
		int id;
	};

	std::vector<float> m_3DGameObjectData;
	std::vector<float> m_Alt3DGameObjectData;

	int m_SampleSize = 50;

};
