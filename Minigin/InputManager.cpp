#include "InputManager.h"

#include "Commands.h"

bool minigin::InputManager::ProcessInput()
{
	if (m_SdlManager.ProcessInput() 
		&& m_ControllerManager.ProcessInput())
		return true;
	return false;
}

void minigin::InputManager::BindToKeyboard(BaseComponent* componentPtr,
	std::function<void(BaseComponent* actor)> function, SDL_KeyCode keyCode, ClickType clickType)
{
	auto bindedFunction = std::bind(function, componentPtr);
	std::unique_ptr<ButtonCommand> buttonCommand{ std::make_unique<ButtonCommand>(bindedFunction) };

	m_SdlManager.AddKeyBoardCommand(keyCode, clickType, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void minigin::InputManager::BindToMouseWheel(BaseComponent* componentPtr,
	std::function<void(BaseComponent* actor, float x)> function)
{
	auto bindedFunction = std::bind(function, componentPtr, std::placeholders::_1);
	std::unique_ptr<ScalarCommand> scalarCommand{ std::make_unique<ScalarCommand>(bindedFunction) };

	m_SdlManager.AddMouseWheelCommand(scalarCommand.get());
	componentPtr->AddCommand(std::move(scalarCommand));
}

void minigin::InputManager::BindToMouseMovement(BaseComponent* componentPtr,
	std::function<void(BaseComponent* actor, float x, float y)> function)
{
	auto bindedFunction = std::bind(function, componentPtr, std::placeholders::_1, std::placeholders::_2);
	std::unique_ptr<VectorCommand> vectorCommand{ std::make_unique<VectorCommand>(bindedFunction) };

	m_SdlManager.AddMouseMovementCommand(vectorCommand.get());
	componentPtr->AddCommand(std::move(vectorCommand));
}

void minigin::InputManager::BindToMouseClick(BaseComponent* componentPtr, std::function<void(BaseComponent* actor)> function,
	MouseButton mouseButton, ClickType clickType)
{
	auto bindedFunction = std::bind(function, componentPtr);
	std::unique_ptr<ButtonCommand> buttonCommand{ std::make_unique<ButtonCommand>(bindedFunction) };

	m_SdlManager.AddMouseButtonCommand(mouseButton, clickType, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void minigin::InputManager::BindToControllerButton(BaseComponent* componentPtr,
	std::function<void(BaseComponent* actor)> function, int controllerIdx, ControllerButton button, ClickType clickType)
{
	auto bindedFunction = std::bind(function, componentPtr);
	std::unique_ptr<ButtonCommand> buttonCommand{ std::make_unique<ButtonCommand>(bindedFunction) };

	m_ControllerManager.AddButtonCommand(controllerIdx, button, clickType, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void minigin::InputManager::BindToControllerTrigger(BaseComponent* componentPtr,
	std::function<void(BaseComponent* actor, float x)> function, int controllerIdx, bool isLeft)
{
	auto bindedFunction = std::bind(function, componentPtr, std::placeholders::_1);
	std::unique_ptr<ScalarCommand> buttonCommand{ std::make_unique<ScalarCommand>(bindedFunction) };

	m_ControllerManager.AddTriggerCommand(controllerIdx, isLeft, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void minigin::InputManager::BindToControllerThumbStick(BaseComponent* componentPtr,
	std::function<void(BaseComponent* actor, float x, float y)> function, int controllerIdx, bool isLeft)
{
	auto bindedFunction = std::bind(function, componentPtr, std::placeholders::_1, std::placeholders::_2);
	std::unique_ptr<VectorCommand> buttonCommand{ std::make_unique<VectorCommand>(bindedFunction) };

	m_ControllerManager.AddThumbStickCommand(controllerIdx, isLeft, buttonCommand.get());
	componentPtr->AddCommand(std::move(buttonCommand));
}

void minigin::InputManager::RemoveCommand(BaseCommand* commandPtr)
{
	m_ControllerManager.RemoveCommand(commandPtr);
	m_SdlManager.RemoveCommand(commandPtr);

}

