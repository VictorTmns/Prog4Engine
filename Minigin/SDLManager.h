#pragma once
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <unordered_map>


#include "Commands.h"
#include "InputTypes.h"

namespace minigin
{
	

	class SDLManager final
	{
	public:

		bool ProcessInput();

		void AddKeyBoardCommand(SDL_KeyCode keyCode, ClickType clickType, ButtonCommand* commandPtr);
		void AddMouseButtonCommand(MouseButton mouseButton, ClickType clickType, ButtonCommand* commandPtr);
		void AddMouseMovementCommand(VectorCommand* commandPtr);
		void AddMouseWheelCommand(ScalarCommand* commandPtr);

		void RemoveCommand(BaseCommand* commandPtr);
	private:

		struct CommandType
		{
			InputType inputType;
			ClickType clickType = static_cast<ClickType>(0);
			int keycode = 0;

			// Overload the == operator
			bool operator==(const CommandType& other) const {
				return (inputType == other.inputType &&
					clickType == other.clickType &&
					keycode == other.keycode);
			}
		};

		struct CommandTypeHash {
			std::size_t operator()(const CommandType& cmd) const {
				// Use a combination of hashes of the individual members
				return std::hash<int>()(static_cast<int>(cmd.inputType)) ^
					std::hash<int>()(static_cast<int>(cmd.clickType)) ^
					std::hash<int>()(cmd.keycode);
			}
		};

		std::unordered_multimap<CommandType, BaseCommand*, CommandTypeHash> m_Commands;

		void HandleKeyButtonEvent(SDL_Event& e);
		void CallAllMouseMovementCommands(float x, float y);
		void CallAllMouseWheelCommands(float x);
		//std::unordered_multimap<SDL_Keycode, BaseCommand*> m_KeyboardUpCommands;
		//std::unordered_multimap<SDL_Keycode, BaseCommand*> m_KeyboardDownCommands;
		//
		//std::unordered_multimap<SDL_Keycode, BaseCommand*> m_MouseButtonDownCommands;
		//std::unordered_multimap<SDL_Keycode, BaseCommand*> m_MouseButtonUpCommands;
		//
		//
		//std::unordered_multimap<SDL_Keycode, BaseCommand*> m_KeyboardPressedCommands;
	};
	};
