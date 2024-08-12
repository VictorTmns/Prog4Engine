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

#include "CreateEnemies.h"
#include "Minigin.h"
#include "Scene.h"
#include "ResourceManager.h"

#include "CreatePlayer.h"
#include "CreateWall.h"
#include "ReadLevelFromFile.h"


void load(vic::Minigin*)
{

	vic::Scene* level1 = vic::SceneManager::GetInstance().CreateScene("level 1");
	//CreatePlayer(level1, glm::vec2{50, 50}, 0);
	//CreateWall(level1, glm::vec2{ 100, 100 });
	//CreateWall(level1, glm::vec2{ 300, 100 });
	//
	//CreateEnemy(level1, glm::vec2{ 400, 400 }, false);
	ReadLevelFromFile(level1, "../Data/Levels/level1.txt");
}


int main(int, char* []) {


	vic::Minigin engine("../Data/Testing/");
	engine.Run(load);



	return 0;
}

