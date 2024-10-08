﻿#include "SDLInputManager.h"
#include <SDL.h>
#include <../imgui-1.90.4/backends/imgui_impl_sdl2.h>

#include "Commands.h"
#include "InputManager.h"


bool vic::SDLInputManager::ProcessInput()
{
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	const Uint32 mouseButtons = SDL_GetMouseState(nullptr, nullptr);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			return false;
		}
		switch (e.type)
		{
		case SDL_KEYUP:
		case SDL_KEYDOWN:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			HandleKeyButtonEvent(e);
			break;
		case SDL_MOUSEMOTION:
			CallAllMouseMovementCommands(static_cast<float>(e.motion.x), static_cast<float>(e.motion.y));
		case SDL_MOUSEWHEEL:
			CallAllMouseWheelCommands(static_cast<float>(e.motion.y));
		default: ;
		}
		
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	for (const auto& command : m_Commands)
	{
		switch (command.first.inputType)
		{
		case InputType::keyboard:
			if ((command.first.clickType == ClickType::hold)
				&& keys[SDL_GetScancodeFromKey(command.first.keycode)])
			{
				ButtonCommand* buttonCommand{ dynamic_cast<ButtonCommand*>(command.second) };
				assert(buttonCommand);
				buttonCommand->Execute();
			}
			break;
		case InputType::mouseButton:
			if ((command.first.clickType == ClickType::hold)
				&& (mouseButtons & SDL_BUTTON(command.first.keycode) ))
			{
				ButtonCommand* buttonCommand{ dynamic_cast<ButtonCommand*>(command.second) };
				assert(buttonCommand);
				buttonCommand->Execute();
			}
			break;
		default: 
			break;
		}
	}


	// Save previous state
	m_PreviousKeyStates = m_CurrentKeyStates;

	// Get current state
	const Uint8* currentKeyStateArray = SDL_GetKeyboardState(NULL);

	// Update key states
	for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
		m_CurrentKeyStates[static_cast<SDL_Scancode>(i)] = currentKeyStateArray[i] != 0;
	}

	return true;
}

void vic::SDLInputManager::AddKeyBoardCommand(SDL_KeyCode keyCode, ClickType clickType, ButtonCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{  InputType::keyboard, clickType, keyCode },
			commandPtr
	});
}
void vic::SDLInputManager::AddMouseButtonCommand(MouseButton mouseButton, ClickType clickType, ButtonCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{ InputType::mouseButton, clickType, static_cast<int>( mouseButton) },
			commandPtr
	});
}
void vic::SDLInputManager::AddMouseMovementCommand(VectorCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{ InputType::mouseMovement, {}, {} },
			commandPtr
	});
}
void vic::SDLInputManager::AddMouseWheelCommand(ScalarCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{ InputType::mouseWheel, {}, {} },
			commandPtr
	});
}

bool vic::SDLInputManager::KeyPressed(SDL_KeyCode key) const
 {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
	return m_CurrentKeyStates.at(scancode) && !m_PreviousKeyStates.at(scancode);
}

bool vic::SDLInputManager::KeyDown(SDL_KeyCode key) const
 {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
	return m_CurrentKeyStates.at(scancode);
}

bool vic::SDLInputManager::KeyUp(SDL_KeyCode key) const
{
	SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
	return !m_CurrentKeyStates.at(scancode) && m_PreviousKeyStates.at(scancode);
}

void vic::SDLInputManager::RemoveCommand(BaseCommand* commandPtr)
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

void vic::SDLInputManager::HandleKeyButtonEvent(SDL_Event& e)
{
	CommandType searchCriterea{};

	if (e.key.state == SDL_PRESSED)
		searchCriterea.clickType = ClickType::pressed;
	else if (e.key.state == SDL_RELEASED)
		searchCriterea.clickType = ClickType::released;
	else
		return;

	if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN)
	{
		searchCriterea.inputType = InputType::keyboard;
		searchCriterea.keycode = e.key.keysym.sym;
	}
	else
	{
		searchCriterea.inputType = InputType::mouseButton;
		searchCriterea.keycode = e.button.button;
	}



	auto range = m_Commands.equal_range(searchCriterea);


	for (auto it = range.first; it != range.second; ++it) 
	{
		ButtonCommand* buttonCommand{ dynamic_cast<ButtonCommand*>(it->second) };
		assert(buttonCommand);
		buttonCommand->Execute();
		
	}
}

void vic::SDLInputManager::CallAllMouseMovementCommands(float x, float y) {
	static CommandType searchCriterea{InputType::mouseMovement};
	auto range = m_Commands.equal_range(searchCriterea);

	for (auto it = range.first; it != range.second; ++it)
	{
		VectorCommand* vectorCommand{ dynamic_cast<VectorCommand*>(it->second) };
		assert(vectorCommand);
		vectorCommand->Execute(-x, y);
	}
}
void vic::SDLInputManager::CallAllMouseWheelCommands(float x) {
	static CommandType searchCriterea{ InputType::mouseWheel };
	auto range = m_Commands.equal_range(searchCriterea);

	for (auto it = range.first; it != range.second; ++it)
	{
		ScalarCommand* scalarCommand{ dynamic_cast<ScalarCommand*>(it->second) };
		assert(scalarCommand);
		scalarCommand->Execute(x);
	}
}