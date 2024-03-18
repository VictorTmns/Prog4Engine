#pragma once
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>

#include <windows.h>
#include <Xinput.h>

#include "Commands.h"
#include "InputTypes.h"


namespace minigin
{
	class BaseCommand;


	class ControllerManager
	{
	public:
	
		ControllerManager();

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
}
