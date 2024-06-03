#include <string>
#include "GameObject.h"

#include <memory>
#include "Scene.h"

namespace vic
{

	
	GameObject::~GameObject()
	{
		for (int idx = 0; idx < static_cast<int>(m_ComponentPtrs.size()); ++idx)
		{
			m_ComponentPtrs[idx].reset();
		}
	}
	
	// ---- FUNCTIONALITY ----
	
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
	//TODO add this to the transform
	void GameObject::SetLocalTransform(const Transform& newTransform)
	{
		m_LocalTransform = newTransform;
		SetTransformDirty();
	}
	void GameObject::SetLocalTranslate(float x, float y)
	{
		m_LocalTransform.SetPosition(x, y);
		SetTransformDirty();
	}
	void GameObject::SetLocalRotation(double rot)
	{
		m_LocalTransform.SetRotation(rot);
		SetTransformDirty();
	}
	void GameObject::AddLocalTranslate(float x, float y)
	{
		m_LocalTransform.AddPosition(x, y);
		SetTransformDirty();
	}
	void GameObject::AddLocalRotation(double rot)
	{
		m_LocalTransform.AddRotation(rot);
		SetTransformDirty();
	}

	Transform& GameObject::GetLocalTransform()
	{
		return m_LocalTransform;
	}
	
	Transform GameObject::GetWorldTransform()
	{
		if (m_WorldTransformDirty)
		{
			m_WorldTransform = CalculateWorldTransform();
			m_WorldTransformDirty = false;
		}
	
		return m_WorldTransform;
	}
	
	// ---- GAME OBJECT / SCENE GRAPH----
	
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
		if (keepWorldPosition)
			SetLocalTransform(GetWorldTransform() - newParentPtr->GetWorldTransform());
		else
			SetTransformDirty();



		return true;
	}
	
	Transform GameObject::CalculateWorldTransform() const
	{
		if (m_ParentPtr == nullptr) 
			return m_LocalTransform;
		return m_LocalTransform.Multiply(m_ParentPtr->CalculateWorldTransform());
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

	
	void GameObject::SetTransformDirty()
	{
		m_WorldTransformDirty = true;
		for (auto& childPtr : m_ChildPtrs)
		{
			childPtr->SetTransformDirty();
		}
	}
}
