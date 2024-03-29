#pragma once
#include "SceneManager.h"

namespace minigin
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void AddGameObject(std::unique_ptr<GameObject>&& gameObject);
		void DeleteAll();

		void Update();
		void FixedUpdate();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;


	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_GameObjectPtrs;

		static unsigned int m_idCounter; 
	};

}
