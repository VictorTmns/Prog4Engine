#include "SceneManager.h"

#include <iostream>

#include "Scene.h"


vic::SceneManager::~SceneManager() = default;

void vic::SceneManager::CheckOnStart()
{
	for (auto& scene : m_Scenes)
		if(scene->IsEnabled())
			scene->OnStart();
}

vic::SceneManager::SceneManager() = default;

void vic::SceneManager::Update()
{
	for (SIZE_T i = 0; i < m_Scenes.size(); ++i)
	{
		if(m_Scenes[i]->IsEnabled())
		{
			m_Scenes[i]->Update();
			m_Scenes[i]->RemoveDeadGameObjects();
		}
	}
}

void vic::SceneManager::Render(const vic::Renderer* renderer) const
{
	for (const auto& scene : m_Scenes)
		if (scene->IsEnabled())
			scene->Render(renderer);
}

void vic::SceneManager::FixedUpdate()
{
	for (SIZE_T i = 0; i < m_Scenes.size(); ++i)
		if (m_Scenes[i]->IsEnabled())
			m_Scenes[i]->FixedUpdate();
}



vic::Scene* vic::SceneManager::CreateScene(const std::string& name)
{
	assert(!name.empty());
	auto scene = std::unique_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(std::move(scene));
	return m_Scenes.back().get();
}

vic::Scene* vic::SceneManager::GetScene(const std::string& name)
{
	assert(!name.empty());

	auto sceneSearchCrit = [name](const std::unique_ptr<Scene>& scenePtr) -> bool {
		return (scenePtr->Name() == name);
		};

	auto sceneIt = std::find_if(m_Scenes.begin(), m_Scenes.end(), sceneSearchCrit);

	if (sceneIt != m_Scenes.end())
		return sceneIt->get();


	return nullptr;
}