#pragma once
#include <memory>
#include "Commands.h"
#include "InputTypes.h"


namespace vic
{
	class BaseCommand;


	class ControllerManager
	{
	public:
		ControllerManager();
		~ControllerManager();

		ControllerManager(ControllerManager&&) noexcept;
		ControllerManager& operator=(ControllerManager&&) noexcept;


		bool ProcessInput();

		void AddButtonCommand(int controllerIdx, ControllerButton button, ClickType clickType, ButtonCommand* commandPtr);
		void AddTriggerCommand(int controllerIdx, bool isLeft, ScalarCommand* commandPtr);
		void AddThumbStickCommand(int controllerIdx, bool isLeft, VectorCommand* commandPtr);

		bool IsPressed(int controllerIdx, ControllerButton button) const;

		void RemoveCommand(BaseCommand* commandPtr);

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_Impl;
	};
}
