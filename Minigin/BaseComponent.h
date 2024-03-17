#pragma once
#include <memory>
#include <vector>

#include "Commands.h"


namespace minigin
{
	class GameObject;

	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void Render() const {}

		void AddCommand(std::unique_ptr<BaseCommand>&& baseCommand);
		// no copying of components
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	protected:
		BaseComponent(GameObject* ownerPtr);

		GameObject* GetOwner() const { return m_OwnerPtr; }

	private:
		GameObject* m_OwnerPtr;

		std::vector<std::unique_ptr<BaseCommand>> m_Commands;
	};
}

