#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include <chrono>
#include <steam_api_common.h>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"

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

minigin::Minigin::Minigin(const std::string &dataPath)
	: m_Achievement{std::make_unique<AchievementManager>()}
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);
	ResourceManager::GetInstance().Init(dataPath);
	Time::GetInstance().Init(0.02);
}

minigin::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	
	
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void minigin::Minigin::Run(const std::function<void(Minigin*)>& load)
{
	// make sure that Input gets initilized before the scene, otherwise this will mess with the cleanup of commands
	auto& input = InputManager::GetInstance();
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& time = Time::GetInstance();


	SteamAPI_RunCallbacks();
	m_Achievement->RemoveAchievements();

	load(this);


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
		renderer.Render();

		SteamAPI_RunCallbacks();
	}
}

AchievementManager* minigin::Minigin::GetAchievementManager() const
{
	return m_Achievement.get();
}
