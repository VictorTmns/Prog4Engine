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

void load(minigin::Minigin*)
{
}


int main(int, char* []) {


	minigin::Minigin engine("../Data/Testing/");
	engine.Run(load);


	return 0;
}