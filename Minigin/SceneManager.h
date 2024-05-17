#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace minigin
{
	class Renderer;
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);

		void Update();
		void Render(const Renderer* renderer);
		void FixedUpdate();


		~SceneManager() override;

		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<std::unique_ptr<Scene>> m_scenes;
	};
}
