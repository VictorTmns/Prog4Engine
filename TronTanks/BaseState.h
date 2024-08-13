#pragma once
#include <memory>

class BaseState
{
public:
	virtual ~BaseState() = default;
	virtual void OnEnter() {}
	virtual void OnExit() {}

	virtual std::unique_ptr<BaseState> Update() = 0;
};
