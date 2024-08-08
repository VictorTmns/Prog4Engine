#include "SceneManager.h"

#include <iostream>

#include "Scene.h"


vic::SceneManager::~SceneManager() = default;
vic::SceneManager::SceneManager() = default;

void vic::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void vic::SceneManager::Render(const vic::Renderer* renderer)
{
	for (const auto& scene : m_scenes)
	{
		scene->Render(renderer);
	}
}

void vic::SceneManager::FixedUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}



vic::Scene* vic::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::unique_ptr<Scene>(new Scene(name));
	m_scenes.push_back(std::move(scene));
	return m_scenes.back().get();
}

vic::Scene* vic::SceneManager::GetScene(const std::string& name)
{
	assert(name != "");

	auto sceneSearchCrit = [name](const std::unique_ptr<Scene>& scenePtr) -> bool {
		return (scenePtr->Name() == name);
		};

	auto sceneIt = std::find_if(m_scenes.begin(), m_scenes.end(), sceneSearchCrit);

	if (sceneIt != m_scenes.end())
		return sceneIt->get();


	throw std::runtime_error("error scene '" + name + "' not found");
	return nullptr;
}
