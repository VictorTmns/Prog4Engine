#pragma once
#include "BaseComponent.h"
#include "ControllerManager.h"
#include "SDLManager.h"
#include "Singleton.h"


namespace minigin
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void BindToKeyboard(BaseComponent* componentPtr , std::function<void(BaseComponent* actor)> function, SDL_KeyCode keyCode, ClickType clickType);

		void BindToMouseWheel(BaseComponent* componentPtr, std::function<void(BaseComponent* actor, float x)> function);
		void BindToMouseMovement(BaseComponent* componentPtr, std::function<void(BaseComponent* actor, float x, float y)> function);
		void BindToMouseClick(BaseComponent* componentPtr, std::function<void(BaseComponent* actor)> function, MouseButton mouseButton, ClickType clickType);

		void BindToControllerButton(BaseComponent* componentPtr, std::function<void(BaseComponent* actor)> function, int controllerIdx, ControllerButton button, ClickType clickType);
		void BindToControllerTrigger(BaseComponent* componentPtr, std::function<void(BaseComponent* actor, float x)> function, int controllerIdx, bool isLeft);
		void BindToControllerThumbStick(BaseComponent* componentPtr, std::function<void(BaseComponent* actor, float x, float y)> function, int controllerIdx, bool isLeft);

		void RemoveCommand(BaseCommand* commandPtr);

	private:
		ControllerManager m_ControllerManager;
		SDLManager m_SdlManager;
	};

}
