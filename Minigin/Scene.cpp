#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace minigin;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name)
	:m_name(name)
{}

Scene::~Scene() = default;


void Scene::AddGameObject(std::unique_ptr<GameObject>&& gameObject)
{
	m_GameObjectPtrs.emplace_back(std::move(gameObject));
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
	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (auto& gameObjectPtr : m_GameObjectPtrs)
	{
		gameObjectPtr->Render();
	}
}

