#pragma once
#include "BaseComponent.h"
#include "BaseState.h"
#include "Observer.h"

class GameManager final : public vic::BaseComponent
{
public:
	GameManager(vic::GameObject* owner);
	~GameManager() override = default;

	enum class PlayMode
	{
		singleplayer,
		multiplayer,
		versus
	};

	void Update() override;

private:
	std::unique_ptr<BaseState> m_State;
};
