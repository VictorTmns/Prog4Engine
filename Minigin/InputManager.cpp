#include "InputManager.h"
#include "Commands.h"

bool vic::InputManager::ProcessInput()
{
	if (m_SdlManager.ProcessInput() 
		&& m_ControllerManager.ProcessInput())
		return true;
	return false;
}

bool vic::InputManager::KeyPressed(SDL_KeyCode keyCode) const
{
	return m_SdlManager.KeyPressed(keyCode);
}

bool vic::InputManager::KeyDown(SDL_KeyCode keyCode) const
{
	return m_SdlManager.KeyPressed(keyCode);
}

bool vic::InputManager::KeyUp(SDL_KeyCode keyCode) const
{
	return m_SdlManager.KeyPressed(keyCode);
}

bool vic::InputManager::ButtonPressed(int controllerIdx, ControllerButton button) const
{
	return m_ControllerManager.ButtonPressed(controllerIdx, button);
}

bool vic::InputManager::ButtonUp(int controllerIdx, ControllerButton button) const
{
	return m_ControllerManager.ButtonUp(controllerIdx, button);

}

bool vic::InputManager::ButtonDown(int controllerIdx, ControllerButton button) const
{
	return m_ControllerManager.ButtonDown(controllerIdx, button);

}


void vic::InputManager::BindToKeyboard(
	BaseComponent* componentPtr, std::function<void()> function, SDL_KeyCode keyCode, ClickType
	clickType)
{

	std::unique_ptr<ButtonCommand> buttonCommand{ std::make_unique<ButtonCommand>(function) };
	m_SdlManager.AddKeyBoardCommand(keyCode, clickType, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void vic::InputManager::BindToMouseWheel(
	BaseComponent* componentPtr, std::function<void(float x)> function)
{
	std::unique_ptr<ScalarCommand> scalarCommand{ std::make_unique<ScalarCommand>(function) };
	m_SdlManager.AddMouseWheelCommand(scalarCommand.get());
	componentPtr->AddCommand(std::move(scalarCommand));
}

void vic::InputManager::BindToMouseMovement(
	BaseComponent* componentPtr, std::function<void(float x, float y)> function)
{
	std::unique_ptr<VectorCommand> vectorCommand{ std::make_unique<VectorCommand>(function) };
	m_SdlManager.AddMouseMovementCommand(vectorCommand.get());
	componentPtr->AddCommand(std::move(vectorCommand));
}

void vic::InputManager::BindToMouseClick(BaseComponent* componentPtr,
                                             std::function<void()> function, MouseButton mouseButton, ClickType clickType)
{
	std::unique_ptr<ButtonCommand> buttonCommand{ std::make_unique<ButtonCommand>(function) };
	m_SdlManager.AddMouseButtonCommand(mouseButton, clickType, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void vic::InputManager::BindToControllerButton(
	BaseComponent* componentPtr, std::function<void()> function, int controllerIdx, ControllerButton
	button, ClickType clickType)
{
	std::unique_ptr<ButtonCommand> buttonCommand{ std::make_unique<ButtonCommand>(function) };
	m_ControllerManager.AddButtonCommand(controllerIdx, button, clickType, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void vic::InputManager::BindToControllerTrigger(
	BaseComponent* componentPtr, std::function<void(float x)> function, int controllerIdx, bool isLeft)
{
	std::unique_ptr<ScalarCommand> buttonCommand{ std::make_unique<ScalarCommand>(function) };
	m_ControllerManager.AddTriggerCommand(controllerIdx, isLeft, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void vic::InputManager::BindToControllerThumbStick(
	BaseComponent* componentPtr, std::function<void(float x, float y)> function, int controllerIdx, bool isLeft)
{
	std::unique_ptr<VectorCommand> buttonCommand{ std::make_unique<VectorCommand>(function) };
	m_ControllerManager.AddThumbStickCommand(controllerIdx, isLeft, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void vic::InputManager::RemoveCommand(BaseCommand* commandPtr)
{
	m_ControllerManager.RemoveCommand(commandPtr);
	m_SdlManager.RemoveCommand(commandPtr);

}

