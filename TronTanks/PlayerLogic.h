#pragma once
#include "BaseComponent.h"

class PlayerLogic : public vic::BaseComponent
{
public:
	PlayerLogic(vic::GameObject* owner);

	void Hit();
	void RandomSpawn();
};
