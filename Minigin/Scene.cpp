#include "Scene.h"

#include "GameTime.h"

using namespace vic;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name)
	:m_PhysicsEngine{ std::make_unique<PhysicsEngine>()}
	, m_name(name)
{}



GameObject& Scene::CreateGameObject()
{
	m_GameObjectPtrs.emplace_back(std::make_unique<GameObject>(this));
	return *m_GameObjectPtrs.back();
}

void Scene::DeleteAll()
{
	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr.reset();
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
	m_PhysicsEngine->UpdatePhysics();


	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr->FixedUpdate();
	}
}

void Scene::Render(const Renderer* renderer) const
{
	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr->Render(renderer);
	}
}

