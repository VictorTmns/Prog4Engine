#include "ControllerManager.h"

#include <cmath>
#include "Commands.h"
#include "Time.h"

#include <windows.h>
#include <Xinput.h>


#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>

namespace minigin
{
	//========================================================
	//================= IMPLEMENTATION =======================
	//========================================================
	class ControllerManager::ControllerImpl
	{
	public:
	
		ControllerImpl();
		~ControllerImpl() = default;


	
		bool ProcessInput();
	
		void AddButtonCommand(int controllerIdx, ControllerButton button, ClickType clickType, ButtonCommand* commandPtr);
		void AddTriggerCommand(int controllerIdx, bool isLeft, ScalarCommand* commantPtr);
		void AddThumbStickCommand(int controllerIdx, bool isLeft, VectorCommand* commandPtr);
	
		void RemoveCommand(BaseCommand* commandPtr);
	
	private:
	
	
		struct CommandType
		{
			int controllerIdx;
	
			InputType inputType;
	
			//For buttons
			ClickType clickType = static_cast<ClickType>(0);
			ControllerButton keycode = static_cast<ControllerButton>(0);
	
			//For thumbstics and triggers
			bool isLeft = false;
	
			bool operator==(const CommandType& other) const {
				return (controllerIdx == other.controllerIdx &&
					inputType == other.inputType &&
					clickType == other.clickType &&
					keycode == other.keycode &&
					isLeft == other.isLeft);
			}
		};
	
		struct CommandTypeHash {
			std::size_t operator()(const CommandType& cmd) const {
				// Use a combination of hashes of the individual members
				return std::hash<int>()(cmd.controllerIdx) ^
					std::hash<int>()(static_cast<int>(cmd.inputType)) ^
					std::hash<int>()(static_cast<int>(cmd.clickType)) ^
					std::hash<int>()(static_cast<int>(cmd.keycode)) ^
					std::hash<bool>()(cmd.isLeft);
			}
		};
	
	
		std::unordered_multimap<CommandType, BaseCommand*, CommandTypeHash> m_Commands;
	
		void HandleButtonCommand(const std::pair<const CommandType&, BaseCommand*>& command);
		void HandleTriggerCommand(const std::pair<const CommandType&, BaseCommand*>& command);
		void HandleThumbStickCommand(const std::pair<const CommandType&, BaseCommand*>& command);
	
	
	
		bool IsDownThisFrame(int controllerIdx, ControllerButton button) const;
		bool IsUpThisFrame(int controllerIdx, ControllerButton button) const;
		bool IsPressed(int controllerIdx, ControllerButton button) const;
		glm::vec2 GetThumbStickNormalized(int controllerIdx, bool leftStick) const;
		float GetTriggerNormalized(int controllerIdx, bool leftTrigger) const;
	
		struct Controller
		{
			bool isActive = false;
			WORD buttonsPressedThisFrame{};
			WORD buttonsReleasedThisFrame{};
			XINPUT_STATE previousState{};
			XINPUT_STATE currentState{};
	
			float timeSinceCheck{};
		};
	
		void ProcessNewControllerState();
	
		std::vector<Controller> m_Controllers;
		float m_InputDeadzone;
	};
	
	
	ControllerManager::ControllerImpl::ControllerImpl()
		: m_InputDeadzone{1500}
		, m_Commands{}
	{
		m_Controllers.resize(XUSER_MAX_COUNT);
	}
	
	
	bool ControllerManager::ControllerImpl::ProcessInput()
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
	
	
	
	void ControllerManager::ControllerImpl::HandleButtonCommand(const std::pair<const CommandType&, BaseCommand*>& command)
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
	void ControllerManager::ControllerImpl::HandleTriggerCommand(const std::pair<const CommandType&, BaseCommand*>& command)
	{
		ScalarCommand* scalarComand{ dynamic_cast<ScalarCommand*>(command.second) };
		assert(scalarComand);
		scalarComand->Execute(GetTriggerNormalized(command.first.controllerIdx, command.first.isLeft));
	}
	void ControllerManager::ControllerImpl::HandleThumbStickCommand(const std::pair<const CommandType&, BaseCommand*>& command)
	{
		VectorCommand* vectorCommand{ dynamic_cast<VectorCommand*>(command.second) };
		assert(vectorCommand);
		glm::vec2 deltaMov{ GetThumbStickNormalized(command.first.controllerIdx, command.first.isLeft) };
		vectorCommand->Execute(deltaMov.x, -deltaMov.y);
	}
	
	void ControllerManager::ControllerImpl::AddButtonCommand(int controllerIdx ,ControllerButton button, ClickType clickType, ButtonCommand* commandPtr)
	{
		m_Commands.insert(std::pair<CommandType, BaseCommand*>{
			CommandType{ controllerIdx, InputType::controllerButton, clickType, button, true},
			commandPtr
		});
	}
	
	void ControllerManager::ControllerImpl::AddTriggerCommand(int controllerIdx , bool isLeft, ScalarCommand* commantPtr)
	{
		m_Commands.insert(std::pair<CommandType, BaseCommand*>{
			CommandType{ controllerIdx, InputType::controllerTrigger, {}, {}, isLeft},
			commantPtr
		});
	}
	
	void ControllerManager::ControllerImpl::AddThumbStickCommand(int controllerIdx, bool isLeft, VectorCommand* commandPtr)
	{
		m_Commands.insert(std::pair<CommandType, BaseCommand*>{
			CommandType{ controllerIdx, InputType::controllerThumbStick, {}, {}, isLeft },
				commandPtr
		});
	}
	
	void ControllerManager::ControllerImpl::RemoveCommand(BaseCommand* commandPtr)
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
	
	
	void ControllerManager::ControllerImpl::ProcessNewControllerState()
	{
		static float connectionTry{5.f};
		for (auto& controller : m_Controllers)
		{
			if(controller.isActive) 
				continue;
	
			controller.timeSinceCheck -= static_cast<float>(Time::GetInstance().GetDeltaTime());
			if(controller.timeSinceCheck < 0)
			{
				controller.isActive = true;
				controller.timeSinceCheck = connectionTry;
			}
		}

		DWORD dwResult;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			if (!m_Controllers[i].isActive)
				continue;
	
			
			CopyMemory(&m_Controllers[i].previousState, &m_Controllers[i].currentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_Controllers[i].currentState, sizeof(XINPUT_STATE));
			
	
			// Simply get the state of the controller from XInput.
			dwResult = XInputGetState(i, &m_Controllers[i].currentState);
	
			if (!dwResult == ERROR_SUCCESS)
			{
				m_Controllers[i].isActive = false;
				continue;
			}

			if( m_Controllers[i].currentState.dwPacketNumber == m_Controllers[i].previousState.dwPacketNumber)
			{
				auto buttonChanges = m_Controllers[i].currentState.Gamepad.wButtons ^ m_Controllers[i].previousState.Gamepad.wButtons;
				m_Controllers[i].buttonsPressedThisFrame = buttonChanges & m_Controllers[i].currentState.Gamepad.wButtons;
				m_Controllers[i].buttonsReleasedThisFrame = buttonChanges & (~m_Controllers[i].currentState.Gamepad.wButtons);
			}

		}
	}
	
	glm::vec2 ControllerManager::ControllerImpl::GetThumbStickNormalized(int controllerIdx, bool leftStick) const
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
		const float normalizedLX = LX / magnitude;
		const float normalizedLY = LY / magnitude;
	
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
	
		return glm::vec2{ normalizedLX * normalizedMagnitude, normalizedLY * normalizedMagnitude };
	}
	float ControllerManager::ControllerImpl::GetTriggerNormalized(int controllerIdx, bool leftTrigger) const
	{
		static float maxTriggerValue{ 255 };
	
	
		if (leftTrigger)
			return m_Controllers[controllerIdx].currentState.Gamepad.bLeftTrigger / maxTriggerValue;
		else
			return m_Controllers[controllerIdx].currentState.Gamepad.bRightTrigger / maxTriggerValue;
	}
	bool ControllerManager::ControllerImpl::IsDownThisFrame(int controllerIdx, ControllerButton button) const
	{
		return m_Controllers[controllerIdx].buttonsPressedThisFrame & static_cast<unsigned int>(button);
	}
	bool ControllerManager::ControllerImpl::IsUpThisFrame(int controllerIdx, ControllerButton button) const
	{
		return m_Controllers[controllerIdx].buttonsReleasedThisFrame & static_cast<unsigned int>(button);
	}
	bool ControllerManager::ControllerImpl::IsPressed(int controllerIdx, ControllerButton button) const
	{
		return m_Controllers[controllerIdx].currentState.Gamepad.wButtons & static_cast<unsigned int>(button);
	}




	//========================================================
	//================= WRAPPER CLASS ========================
	//========================================================

	ControllerManager::ControllerManager()
		: m_Impl{ std::make_unique<ControllerImpl>() }
	{
	}

	ControllerManager::~ControllerManager() = default;

	ControllerManager::ControllerManager(ControllerManager&&) noexcept = default;

	ControllerManager& ControllerManager::operator=(ControllerManager&&) noexcept = default;

	bool ControllerManager::ProcessInput()
	{
		return m_Impl->ProcessInput();
	}

	void ControllerManager::AddButtonCommand(int controllerIdx, ControllerButton button, ClickType clickType,
		ButtonCommand* commandPtr)
	{
		m_Impl->AddButtonCommand(controllerIdx, button, clickType, commandPtr);
	}

	void ControllerManager::AddTriggerCommand(int controllerIdx, bool isLeft, ScalarCommand* commandPtr)
	{
		m_Impl->AddTriggerCommand(controllerIdx, isLeft, commandPtr);
	}

	void ControllerManager::AddThumbStickCommand(int controllerIdx, bool isLeft, VectorCommand* commandPtr)
	{
		m_Impl->AddThumbStickCommand(controllerIdx, isLeft, commandPtr);
	}

	void ControllerManager::RemoveCommand(BaseCommand* commandPtr)
	{
		m_Impl->RemoveCommand(commandPtr);
	}
}
