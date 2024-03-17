#include "ControllerManager.h"

#include <cmath>
#include "Commands.h"


minigin::ControllerManager::ControllerManager(): m_InputDeadzone{0}
{
	m_Controllers.resize(XUSER_MAX_COUNT);
}


bool minigin::ControllerManager::ProcessInput()
{
	ProcessNewControllerState();

	for (auto& command : m_Commands)
	{
		switch (command.first.inputType) {
		case InputType::controllerButton:
			HandleButtonCommand(command);
			break;

		case InputType::controllerTrigger:
			HandleTriggerCommand(command);
			break;

		case InputType::controllerThumbStick:
			HandleThumbStickCommand(command);
			break;
		}
	}

	return true;
}



void minigin::ControllerManager::HandleButtonCommand(const std::pair<const CommandType&, BaseCommand*>& command)
{
	ButtonCommand* buttonCommand{ dynamic_cast<ButtonCommand*>(command.second) };
	assert(buttonCommand);

	switch (command.first.clickType) {
	case ClickType::released:
		if (IsUpThisFrame(command.first.controllerIdx, command.first.keycode))
			buttonCommand->Execute();
		break;

	case ClickType::pressed:
		if (IsDownThisFrame(command.first.controllerIdx, command.first.keycode))
			buttonCommand->Execute();
		break;

	case ClickType::hold:
		if (IsPressed(command.first.controllerIdx, command.first.keycode))
			buttonCommand->Execute();
		break;

	}
}
void minigin::ControllerManager::HandleTriggerCommand(const std::pair<const CommandType&, BaseCommand*>& command)
{
	ScalarCommand* scalarComand{ dynamic_cast<ScalarCommand*>(command.second) };
	assert(scalarComand);
	scalarComand->Execute(GetTriggerNormalized(command.first.controllerIdx, command.first.isLeft));
}
void minigin::ControllerManager::HandleThumbStickCommand(const std::pair<const CommandType&, BaseCommand*>& command)
{
	VectorCommand* vectorCommand{ dynamic_cast<VectorCommand*>(command.second) };
	assert(vectorCommand);
	glm::vec2 deltaMov{ GetThumbStickNormalized(command.first.controllerIdx, command.first.isLeft) };
	vectorCommand->Execute(deltaMov.x, deltaMov.y);
}

void minigin::ControllerManager::AddButtonCommand(int controllerIdx ,ControllerButton button, ClickType clickType, ButtonCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{ controllerIdx, InputType::controllerButton, clickType, button, true},
		commandPtr
	});
}

void minigin::ControllerManager::AddTriggerCommand(int controllerIdx , bool isLeft, ScalarCommand* commantPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{ controllerIdx, InputType::controllerTrigger, {}, {}, isLeft},
		commantPtr
	});
}

void minigin::ControllerManager::AddThumbStickCommand(int controllerIdx, bool isLeft, VectorCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{ controllerIdx, InputType::controllerThumbStick, {}, {}, isLeft },
			commandPtr
	});
}

void minigin::ControllerManager::RemoveCommand(BaseCommand* commandPtr)
{
	for (auto it = m_Commands.begin(); it != m_Commands.end(); ) {
		if (it->second == commandPtr) {
			it = m_Commands.erase(it);
		}
		else {
			++it;
		}
	}
}


void minigin::ControllerManager::ProcessNewControllerState()
{

	// TODO don't check unused controllers every frame for state
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{


		if (m_Controllers[i].isActive)
		{
			CopyMemory(&m_Controllers[i].previousState, &m_Controllers[i].currentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_Controllers[i].currentState, sizeof(XINPUT_STATE));
		}

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &m_Controllers[i].currentState);

		if (dwResult == ERROR_SUCCESS
			&& m_Controllers[i].currentState.dwPacketNumber == m_Controllers[i].previousState.dwPacketNumber)
		{
			m_Controllers[i].isActive = true;
			auto buttonChanges = m_Controllers[i].currentState.Gamepad.wButtons ^ m_Controllers[i].previousState.Gamepad.wButtons;
			m_Controllers[i].buttonsPressedThisFrame = buttonChanges & m_Controllers[i].currentState.Gamepad.wButtons;
			m_Controllers[i].buttonsReleasedThisFrame = buttonChanges & (~m_Controllers[i].currentState.Gamepad.wButtons);
		}
		else
		{
			m_Controllers[i].isActive = false;
		}
	}
}

glm::vec2 minigin::ControllerManager::GetThumbStickNormalized(int controllerIdx, bool leftStick) const
{
	static float maxThumbStickValue{ 32767 };

	float LX {};
	float LY {};

	if(leftStick)
	{
		LX = m_Controllers[controllerIdx].currentState.Gamepad.sThumbLX;
		LY = m_Controllers[controllerIdx].currentState.Gamepad.sThumbLY;
	}
	else
	{
		LX = m_Controllers[controllerIdx].currentState.Gamepad.sThumbRX;
		LY = m_Controllers[controllerIdx].currentState.Gamepad.sThumbRY;
	}

	//determine how far the controller is pushed
	float magnitude = sqrt(LX * LX + LY * LY);

	//determine the direction the controller is pushed
	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	float normalizedMagnitude{};

	//check if the controller is outside a circular dead zone
	if (magnitude > m_InputDeadzone)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > maxThumbStickValue) magnitude = maxThumbStickValue;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= m_InputDeadzone;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (maxThumbStickValue - m_InputDeadzone);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
		return glm::vec2{};
	}

	return glm::vec2{ normalizedLX * normalizedMagnitude, normalizedLY * normalizedLY };
}
float minigin::ControllerManager::GetTriggerNormalized(int controllerIdx, bool leftTrigger) const
{
	static float maxTriggerValue{ 255 };


	if (leftTrigger)
		return m_Controllers[controllerIdx].currentState.Gamepad.bLeftTrigger / maxTriggerValue;
	else
		return m_Controllers[controllerIdx].currentState.Gamepad.bRightTrigger / maxTriggerValue;
}
bool minigin::ControllerManager::IsDownThisFrame(int controllerIdx, ControllerButton button) const
{
	return m_Controllers[controllerIdx].buttonsPressedThisFrame & static_cast<unsigned int>(button);
}
bool minigin::ControllerManager::IsUpThisFrame(int controllerIdx, ControllerButton button) const
{
	return m_Controllers[controllerIdx].buttonsReleasedThisFrame & static_cast<unsigned int>(button);
}
bool minigin::ControllerManager::IsPressed(int controllerIdx, ControllerButton button) const
{
	return m_Controllers[controllerIdx].currentState.Gamepad.wButtons & static_cast<unsigned int>(button);
}

