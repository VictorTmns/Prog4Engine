#include "SceneManager.h"
#include "Scene.h"


minigin::SceneManager::~SceneManager() = default;
minigin::SceneManager::SceneManager() = default;

void minigin::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void minigin::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void minigin::SceneManager::FixedUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}



minigin::Scene* minigin::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::unique_ptr<Scene>(new Scene(name));
	m_scenes.push_back(std::move(scene));
	return m_scenes.back().get();
}
