#pragma once

class BaseState
{
public:
	virtual ~BaseState() = default;
	virtual void OnEnter() {}
	virtual void OnExit() {}

	virtual void Update() = 0;
};
