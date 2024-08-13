#pragma once
#include "BaseComponent.h"
#include "ControllerManager.h"
#include "SDLInputManager.h"
#include "Singleton.h"


namespace vic
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		bool ButtonPressed(SDL_KeyCode keyCode) const;
		bool ButtonPressed(int controllerIdx, ControllerButton button) const;


		void BindToKeyboard(BaseComponent* componentPtr, std::function<void()> function, SDL_KeyCode keyCode, ClickType clickType);

		void BindToMouseWheel(BaseComponent* componentPtr, std::function<void( float x)> function);
		void BindToMouseMovement(BaseComponent* componentPtr, std::function<void( float x, float y)> function);
		void BindToMouseClick(BaseComponent* componentPtr, std::function<void()> function, MouseButton mouseButton, ClickType clickType);

		void BindToControllerButton(BaseComponent* componentPtr, std::function<void()> function, int controllerIdx, ControllerButton button, ClickType clickType);
		void BindToControllerTrigger(BaseComponent* componentPtr, std::function<void( float x)> function, int controllerIdx, bool isLeft);
		void BindToControllerThumbStick(BaseComponent* componentPtr, std::function<void( float x, float y)> function, int controllerIdx, bool isLeft);

		void RemoveCommand(BaseCommand* commandPtr);

	private:
		ControllerManager m_ControllerManager;
		SDLInputManager m_SdlManager;
	};

}
