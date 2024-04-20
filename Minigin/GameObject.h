#pragma once
#include <memory>
#include <vector>

#include "Transform.h"
#include "BaseComponent.h"
#include "Observer.h"

namespace minigin
{
	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void Render() const;
		void SetLocalTransform(const Transform& newTransform);


		void SetLocalTranslate(float x, float y);
		void SetLocalRotation(double rot);
		void AddLocalTranslate(float x, float y);
		void AddLocalRotation(double rot);
		Transform GetLocalTransform();
		Transform GetWorldTransform();

		//Components

		template <typename T, typename ... Args> T* AddComponent(Args&& ... args);
		template<typename T> void RemoveComponent();
		template<typename T> T* GetComponent();
		template<typename T> bool HasComponent();


		//GameObjects
		bool SetParent(GameObject* newParentPtr, bool keepWorldPosition = false);

		GameObject* GetParent() const { return m_ParentPtr; }
		int GetChildCount() const { return static_cast<int>(m_ChilderenPtrs.size()); }
		GameObject* GetChildAt(int index) const { return m_ChilderenPtrs[index]; }
		bool IsChild(GameObject* gameObject) const;

		//Consturctors and destructors

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_WorldTransformDirty{true};
		Transform m_WorldTransform{};
		Transform m_LocalTransform{};

		std::vector<std::unique_ptr<BaseComponent>> m_ComponentPtrs;

		GameObject* m_ParentPtr = nullptr;
		std::vector<GameObject*> m_ChilderenPtrs {};

		Transform CalculateWorldTransform() const;


		void AddChild(GameObject* childPtr);
		void RemoveChild(GameObject* childToRemovePtr);


		void SetTransformDirty();
	};

	template<typename T, typename... Args>
	T* GameObject::AddComponent(Args&&... args) {

		static_assert(std::is_base_of_v<BaseComponent, T>, "T must derive from BaseComponent");
		std::unique_ptr<T> newComponent = std::make_unique<T>(this, std::forward<Args>(args)...);
		T* newComponentPtr = newComponent.get();
		m_ComponentPtrs.push_back(std::move(newComponent));
		return newComponentPtr;
	}

	template<typename T>
	void GameObject::RemoveComponent()
	{
		for (auto componentPtr = m_ComponentPtrs.begin(); componentPtr != m_ComponentPtrs.end(); ++componentPtr)
		{
			T* castedPtr = dynamic_cast<T*>(componentPtr->get());
			if (castedPtr != nullptr)
			{
				m_ComponentPtrs.erase(componentPtr);
				return;
			}
		}
	}

	template <typename T>
	T* GameObject::GetComponent()
	{
		for (auto componentPtr = m_ComponentPtrs.begin(); componentPtr != m_ComponentPtrs.end(); ++componentPtr)
		{
			T* castedPtr = dynamic_cast<T*>(componentPtr->get());
			if (castedPtr != nullptr)
			{
				return castedPtr;
			}
		}
		return nullptr;
	}
	template <typename T>
	bool GameObject::HasComponent()
	{
		for (auto componentPtr = m_ComponentPtrs.begin(); componentPtr != m_ComponentPtrs.end(); ++componentPtr)
		{
			T* castedPtr = dynamic_cast<T*>(componentPtr->get());
			if (castedPtr != nullptr)
			{
				return true;
			}
		}
		return false;
	}
}
