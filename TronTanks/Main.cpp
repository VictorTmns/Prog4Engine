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

void BuildPlayer(vic::Minigin* engine);

void load(vic::Minigin* engine)
{

	vic::SceneManager::GetInstance().CreateScene("world");
	BuildPlayer(engine);
}


int main(int, char* []) {


	vic::Minigin engine("../Data/Testing/");
	engine.Run(load);



	return 0;
}

void BuildPlayer([[maybe_unused]] vic::Minigin* engine)
{
	vic::Scene* scene = vic::SceneManager::GetInstance().GetScene("world");

	[[maybe_unused]] vic::GameObject& player{ scene->CreateGameObject() };
}
