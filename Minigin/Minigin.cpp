#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <stdexcept>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include "SoundSystemSDL.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

vic::Minigin::Minigin(const std::string &resourceDataPath)
{
	try
	{
		Init(resourceDataPath);
	}
	catch (std::runtime_error& err)
	{
		std::cerr << err.what();
		std::abort();
	}
}

vic::Minigin::~Minigin()
{
	
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void vic::Minigin::Run(const std::function<void(Minigin*)>& load)
{
	// make sure that Input gets initialized before the scene, otherwise this will mess with the cleanup of commands
	auto& input = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& time = GameTime::GetInstance();



	load(this);
	sceneManager.OnStart();

	bool doContinue = true;
	while (doContinue)
	{
		time.Update();

		doContinue = input.ProcessInput();
		while (time.LagRemaining())
		{
			sceneManager.FixedUpdate();
		}

		sceneManager.Update();
		m_Renderer->Render();



		std::this_thread::sleep_for(GameTime::GetInstance().SleepTime());
	}
}


void vic::Minigin::Init(const std::string& resourceDataPath)
{

	PrintSDLVersion();

	m_Renderer = std::make_unique<Renderer>();

	ResourceManager::GetInstance().Init(resourceDataPath, m_Renderer.get());
	GameTime::GetInstance().Init(0.02, 120);

	ServiceLocator::RegisterSoundSystem(std::make_unique<SoundSystemSDL>());

}
