#include <string>
#include "GameObject.h"

#include <memory>
#include "Scene.h"

namespace vic
{

	GameObject::GameObject(Scene* scenePtr, std::string name)
		: m_Name{std::move(name)}
		  , m_Transform{std::make_unique<Transform>(this)}
		  , m_ScenePtr{scenePtr}
	{
	}

	GameObject::~GameObject()
	{
		for (auto childPtr : m_ChildPtrs)
		{
			childPtr->Destroy();
		}
	}


	// ---- FUNCTIONALITY ----

	void GameObject::OnSceneStart()
	{
		for (auto& pComponent : m_ComponentPtrs)
		{
			pComponent->OnSceneStart();
		}
	}

	void GameObject::Update()
	{
		for (auto& pComponent : m_ComponentPtrs)
		{
			pComponent->Update();
		}
	}
	
	void GameObject::FixedUpdate()
	{
		for (auto& pComponent : m_ComponentPtrs)
		{
			pComponent->FixedUpdate();
		}
	}
	
	void GameObject::Render(const Renderer* renderer) const
	{
		for (const auto& pComponent : m_ComponentPtrs)
		{
			pComponent->Render(renderer);
		}
	}

	// ---- TRANSFORM ----

	
	// ---- GAME OBJECT / SCENE GRAPH----

	void GameObject::Destroy()
	{
		m_Dead = true;
		for (auto& childPtr : m_ChildPtrs)
			childPtr->Destroy();
	}

	bool GameObject::SetParent(GameObject* newParentPtr, bool keepWorldPosition)
	{
		// 1 check if parent is valid
		if (newParentPtr == nullptr
			|| newParentPtr == this
			|| newParentPtr == m_ParentPtr
			|| IsChild(newParentPtr)) 
			return false;

		// 2 Remove self from current parent
		if (m_ParentPtr)
			m_ParentPtr->RemoveChild(this);
	

		// 3 Change own parentPtr
		m_ParentPtr = newParentPtr;

		// 4 Add self to new parent
		m_ParentPtr->AddChild(this);


		// 5 Update Transforms
		m_Transform->SetNewParent(newParentPtr, keepWorldPosition);



		return true;
	}
	

	
	void GameObject::AddChild(GameObject* newChildPtr)
	{
		m_ChildPtrs.emplace_back(newChildPtr);
	}

	void GameObject::RemoveChild(GameObject* childToRemovePtr)
	{
		for (auto childIt = m_ChildPtrs.begin(); childIt != m_ChildPtrs.end(); ++childIt)
		{
			if (*childIt == childToRemovePtr)
			{
				m_ChildPtrs.erase(childIt);
				return;
			}
		}

		assert(false && "parent thinks it doesn't own child");
		return;
	}
	
	
	bool GameObject::IsChild(GameObject* gameObject) const
	{
		for (auto& childPtr : m_ChildPtrs)
		{
			if (childPtr == gameObject) return true; //check if the child is that gameObject
			if (childPtr->IsChild(gameObject)) return true; //recursivly checks if one of its childeren is that gameObject
		}
	
		return false;
	}




	// ---- COMPONENTS ----

	

}
