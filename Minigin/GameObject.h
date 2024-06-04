#pragma once
#include <memory>
#include <vector>

#include "Transform.h"
#include "BaseComponent.h"
#include "Observer.h"
#include "Renderer.h"

namespace vic
{
	class Scene;

	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void Render(const Renderer* renderer) const;

		
		Transform& GetTransform() const { return *m_Transform; }


		//Components

		template <typename T, typename ... Args> T* AddComponent(Args&& ... args)
			requires std::is_base_of_v<BaseComponent, T>;
		template<typename T> void RemoveComponent()
			requires std::is_base_of_v<BaseComponent, T>;
		template<typename T> T* GetComponent()
			requires std::is_base_of_v<BaseComponent, T>;
		template<typename T> bool HasComponent()
			requires std::is_base_of_v<BaseComponent, T>;


		//GameObjects
		bool SetParent(GameObject* newParentPtr, bool keepWorldPosition = false);

		GameObject* GetParent() const { return m_ParentPtr; }
		int GetChildCount() const { return static_cast<int>(m_ChildPtrs.size()); }
		GameObject* GetChildAt(int index) const { return m_ChildPtrs[index]; }
		bool IsChild(GameObject* gameObject) const;

		//Constructors and destructors

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::unique_ptr<Transform> m_Transform;

		std::vector<std::unique_ptr<BaseComponent>> m_ComponentPtrs;

		GameObject* m_ParentPtr = nullptr;
		std::vector<GameObject*> m_ChildPtrs {};


		void AddChild(GameObject* childPtr);
		void RemoveChild(GameObject* childToRemovePtr);
	};

	template<typename T, typename... Args>
	T* GameObject::AddComponent(Args&&... args)
		requires std::is_base_of_v<BaseComponent, T>
	{

		static_assert(std::is_base_of_v<BaseComponent, T>, "T must derive from BaseComponent");
		std::unique_ptr<T> newComponent = std::make_unique<T>(this, std::forward<Args>(args)...);
		T* newComponentPtr = newComponent.get();
		m_ComponentPtrs.push_back(std::move(newComponent));
		return newComponentPtr;
	}

	template<typename T>
	void GameObject::RemoveComponent()
		requires std::is_base_of_v<BaseComponent, T>
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
		requires std::is_base_of_v<BaseComponent, T>
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
		requires std::is_base_of_v<BaseComponent, T>
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
