#include "InputManager.h"

#include "Commands.h"
#include "KeyboardTestComponent.h"

bool minigin::InputManager::ProcessInput()
{
	if (m_SdlManager.ProcessInput() 
		&& m_ControllerManager.ProcessInput())
		return true;
	return false;
}

void minigin::InputManager::BindToKeyboard(
	minigin::BaseComponent* componentPtr, std::function<void()> function, SDL_KeyCode keyCode, minigin::ClickType
	clickType)
{

	std::unique_ptr<ButtonCommand> buttonCommand{ std::make_unique<ButtonCommand>(function) };
	m_SdlManager.AddKeyBoardCommand(keyCode, clickType, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
	function();
}

void minigin::InputManager::BindToMouseWheel(
	minigin::BaseComponent* componentPtr, std::function<void(float x)> function)
{
	std::unique_ptr<ScalarCommand> scalarCommand{ std::make_unique<ScalarCommand>(function) };
	m_SdlManager.AddMouseWheelCommand(scalarCommand.get());
	componentPtr->AddCommand(std::move(scalarCommand));
}

void minigin::InputManager::BindToMouseMovement(
	minigin::BaseComponent* componentPtr, std::function<void(float x, float y)> function)
{
	std::unique_ptr<VectorCommand> vectorCommand{ std::make_unique<VectorCommand>(function) };
	m_SdlManager.AddMouseMovementCommand(vectorCommand.get());
	componentPtr->AddCommand(std::move(vectorCommand));
}

void minigin::InputManager::BindToMouseClick(minigin::BaseComponent* componentPtr,
                                             std::function<void()> function, minigin::MouseButton mouseButton, minigin::ClickType clickType)
{
	std::unique_ptr<ButtonCommand> buttonCommand{ std::make_unique<ButtonCommand>(function) };
	m_SdlManager.AddMouseButtonCommand(mouseButton, clickType, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void minigin::InputManager::BindToControllerButton(
	minigin::BaseComponent* componentPtr, std::function<void()> function, int controllerIdx, minigin::ControllerButton
	button, minigin::ClickType clickType)
{
	std::unique_ptr<ButtonCommand> buttonCommand{ std::make_unique<ButtonCommand>(function) };
	m_ControllerManager.AddButtonCommand(controllerIdx, button, clickType, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void minigin::InputManager::BindToControllerTrigger(
	minigin::BaseComponent* componentPtr, std::function<void(float x)> function, int controllerIdx, bool isLeft)
{
	std::unique_ptr<ScalarCommand> buttonCommand{ std::make_unique<ScalarCommand>(function) };
	m_ControllerManager.AddTriggerCommand(controllerIdx, isLeft, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void minigin::InputManager::BindToControllerThumbStick(
	minigin::BaseComponent* componentPtr, std::function<void(float x, float y)> function, int controllerIdx, bool isLeft)
{
	std::unique_ptr<VectorCommand> buttonCommand{ std::make_unique<VectorCommand>(function) };
	m_ControllerManager.AddThumbStickCommand(controllerIdx, isLeft, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void minigin::InputManager::RemoveCommand(BaseCommand* commandPtr)
{
	m_ControllerManager.RemoveCommand(commandPtr);
	m_SdlManager.RemoveCommand(commandPtr);

}

