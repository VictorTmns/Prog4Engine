#pragma once

namespace minigin
{

	enum class InputType
	{
		keyboard,

		mouseButton,
		mouseWheel,
		mouseMovement,

		controllerButton,
		controllerTrigger,
		controllerThumbStick
	};

	enum class ClickType
	{
		released,
		pressed,
		hold
	};

	enum class MouseButton
	{
		left = 1,
		middle = 2,
		right = 3,
		x1 = 4,
		x2 = 5
	};



	enum class ControllerButton
	{
		dpadUp = 0x0001,
		dpadDown = 0x0002,
		dpadLeft = 0x0004,
		dpadRight = 0x0008,
		start = 0x0010,
		back = 0x0020,
		leftThumb = 0x0040,
		rightThumb = 0x0080,
		leftShoulder = 0x0100,
		rightShoulder = 0x0200,
		a = 0x0400,
		b = 0x0800,
		x = 0x1000,
		y = 0x2000
	};
}
