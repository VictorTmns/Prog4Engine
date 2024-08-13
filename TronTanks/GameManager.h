#pragma once
#include "BaseComponent.h"
#include "BaseState.h"
#include "Observer.h"

class GameManager : public vic::BaseComponent, public vic::Observer
{
public:
	GameManager(vic::GameObject* owner);
	~GameManager() override = default;

	void Update() override;
	void Notify(Event event, const BaseComponent* subject) override;

private:
	std::unique_ptr<BaseState> m_State;
};
