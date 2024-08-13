#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include "PhysicsEngine.h"

namespace vic
{
	class Scene final
	{
		friend Scene* SceneManager::CreateScene(const std::string& name);
	public:
		GameObject& CreateGameObject(const std::string& name = "");
		void DeleteAll();


		void OnStart();
		void Update();
		void FixedUpdate();
		void Render(const Renderer* renderer) const;
		void RemoveDeadGameObjects();


		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Enable() {m_Enabled = true; }
		void Disable() { m_Enabled = false; }
		bool IsEnabled() const { return m_Enabled; }

		std::string_view Name() const { return std::string_view(m_name); }
		PhysicsEngine& GetPhysicsEngine() const { return *m_PhysicsEngine; }

		std::vector<GameObject*> GetGameObjectsByName(const std::string& name) const;
	private: 
		explicit Scene(const std::string& name);

		bool m_Enabled = true;

		std::unique_ptr<PhysicsEngine> m_PhysicsEngine;

		std::string m_name;
		std::list<std::unique_ptr<GameObject>> m_GameObjectPtrs;

		static unsigned int m_idCounter; 
	};

}
