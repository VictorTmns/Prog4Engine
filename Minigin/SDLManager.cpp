#include "SDLManager.h"
#include <SDL.h>
#include <../imgui-1.90.4/backends/imgui_impl_sdl2.h>

#include "Commands.h"
#include "InputManager.h"


bool minigin::SDLManager::ProcessInput()
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
				&& keys[command.first.keycode])
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

	return true;
}

void minigin::SDLManager::AddKeyBoardCommand(SDL_KeyCode keyCode, ClickType clickType, ButtonCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{  InputType::keyboard, clickType, keyCode },
			commandPtr
	});
}
void minigin::SDLManager::AddMouseButtonCommand(MouseButton mouseButton, ClickType clickType, ButtonCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{ InputType::mouseButton, clickType, static_cast<int>( mouseButton) },
			commandPtr
	});
}
void minigin::SDLManager::AddMouseMovementCommand(VectorCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{ InputType::mouseMovement, {}, {} },
			commandPtr
	});
}
void minigin::SDLManager::AddMouseWheelCommand(ScalarCommand* commandPtr)
{
	m_Commands.insert(std::pair<CommandType, BaseCommand*>{
		CommandType{ InputType::mouseWheel, {}, {} },
			commandPtr
	});
}

void minigin::SDLManager::RemoveCommand(BaseCommand* commandPtr)
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

void minigin::SDLManager::HandleKeyButtonEvent(SDL_Event& e)
{
	CommandType searchCriterea{};

	if (e.key.state == SDL_PRESSED)
		searchCriterea.clickType = ClickType::pressed;
	else
		searchCriterea.clickType = ClickType::released;


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

void minigin::SDLManager::CallAllMouseMovementCommands(float x, float y) {
	static CommandType searchCriterea{InputType::mouseMovement};
	auto range = m_Commands.equal_range(searchCriterea);

	for (auto it = range.first; it != range.second; ++it)
	{
		VectorCommand* vectorCommand{ dynamic_cast<VectorCommand*>(it->second) };
		assert(vectorCommand);
		vectorCommand->Execute(x, y);
	}
}
void minigin::SDLManager::CallAllMouseWheelCommands(float x) {
	static CommandType searchCriterea{ InputType::mouseWheel };
	auto range = m_Commands.equal_range(searchCriterea);

	for (auto it = range.first; it != range.second; ++it)
	{
		ScalarCommand* scalarCommand{ dynamic_cast<ScalarCommand*>(it->second) };
		assert(scalarCommand);
		scalarCommand->Execute(x);
	}
}