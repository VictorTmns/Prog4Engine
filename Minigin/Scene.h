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

		void Update();
		void FixedUpdate();
		void Render(const Renderer* renderer) const;

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::string_view Name() const { return std::string_view(m_name); }

		PhysicsEngine& GetPhysicsEngine() const { return *m_PhysicsEngine; }
	private: 
		explicit Scene(const std::string& name);

		std::unique_ptr<PhysicsEngine> m_PhysicsEngine;

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_GameObjectPtrs;

		static unsigned int m_idCounter; 
	};

}
