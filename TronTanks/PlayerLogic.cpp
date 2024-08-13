#include "PlayerLogic.h"

#include "GameObject.h"

PlayerLogic::PlayerLogic(vic::GameObject* owner)
	: BaseComponent{owner}
{
}

void PlayerLogic::Hit()
{

	NotifyObservers(vic::Observer::Event::playerHit);
}
