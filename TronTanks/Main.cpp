#include "SDL.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#pragma warning (push)
#pragma warning (disable: 4996)
#pragma warning (pop)

#include "Minigin.h"
#include "Scene.h"
#include "ResourceManager.h"

#include "CreatePlayer.h"
#include "CreateWall.h"


void load(vic::Minigin*)
{

	vic::Scene* level1 = vic::SceneManager::GetInstance().CreateScene("level 1");
	BuildPlayer(level1, glm::vec2{50, 50});
	CreateWall(level1, glm::vec2{ 100, 100 });
	CreateWall(level1, glm::vec2{ 300, 100 });
}


int main(int, char* []) {


	vic::Minigin engine("../Data/Testing/");
	engine.Run(load);



	return 0;
}

