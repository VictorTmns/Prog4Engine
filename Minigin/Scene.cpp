#include "Scene.h"

#include "GameTime.h"

using namespace vic;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name)
	:m_PhysicsEngine{ std::make_unique<PhysicsEngine>()}
	, m_name(name)
{}



GameObject& Scene::CreateGameObject(const std::string& name)
{
	m_GameObjectPtrs.emplace_back(std::make_unique<GameObject>(this, name));
	return *m_GameObjectPtrs.back();
}

void Scene::DeleteAll()
{
	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr.reset();
	}
}

void Scene::OnStart()
{
	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr->OnStart();
	}
}

void Scene::Update()
{
	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr->Update();
	}
}

void Scene::FixedUpdate()
{
	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr->FixedUpdate();
	}

	m_PhysicsEngine->CheckColliders();
	m_PhysicsEngine->CheckOverlaps();
}

void Scene::Render(const Renderer* renderer) const
{
	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr->Render(renderer);
	}
}

void Scene::RemoveDeadGameObjects()
{
	m_GameObjectPtrs.remove_if([](const std::unique_ptr<GameObject>& gameObjectPtr) { return gameObjectPtr->IsDead(); });
}

