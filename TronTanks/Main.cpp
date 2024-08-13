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

#include "CreateWall.h"
#include "GameManager.h"


void load(vic::Minigin*)
{

	vic::Scene* managingScene = vic::SceneManager::GetInstance().CreateScene("manager scene");
	managingScene->CreateGameObject("the manager").AddComponent<GameManager>();
}


int main(int, char* [])
{
	vic::Minigin engine("../Data/Testing/");
	engine.Run(load);

	return 0;
}

