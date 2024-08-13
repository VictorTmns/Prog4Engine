#pragma once
#include <memory>
#include <SDL_syswm.h>
#include <vector>

#include "Commands.h"
#include "Observer.h"

namespace vic
{
	class Renderer;
	class GameObject;

	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		virtual void OnSceneStart() {}
		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void Render(const Renderer*) const {}

		void AddCommand(std::unique_ptr<BaseCommand>&& baseCommand);
		void AttachObserver(Observer* observer);
		void RemoveObserver(Observer* observerToRemove);

		// no copying or moving of components
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		void Disable()
		{
			for (auto& baseCommand : m_Commands)
				baseCommand->Disable();
		}
		void Enable()
		{
			for (auto& baseCommand : m_Commands)
				baseCommand->Enable();
		}


		GameObject* Owner() const { return m_OwnerPtr; }
	protected:
		BaseComponent(GameObject* ownerPtr);
		void NotifyObservers(Observer::Event event) const;

		
	private:
		bool m_OnStart = true;

		GameObject* m_OwnerPtr;

		std::vector<std::unique_ptr<BaseCommand>> m_Commands;

		std::vector<Observer*> m_Observers;
	};
}

