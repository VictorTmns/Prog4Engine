#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}


vic::Renderer::Renderer()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	m_renderer = SDL_CreateRenderer(m_window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

vic::Renderer::~Renderer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}


void vic::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);



	SceneManager::GetInstance().Render(this);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

}


void vic::Renderer::RenderCircle(float xCenter, float yCenter, float radius, SDL_Color color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);


	const int32_t diameter { static_cast<int32_t>(radius * 2) };

	const int32_t centerX{ static_cast<int32_t>(xCenter)};
	const int32_t centerY{ static_cast<int32_t>(yCenter)};
	int32_t x = static_cast<int32_t>(radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		// Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(m_renderer, centerX + x, centerY - y);
		SDL_RenderDrawPoint(m_renderer, centerX + x, centerY + y);
		SDL_RenderDrawPoint(m_renderer, centerX - x, centerY - y);
		SDL_RenderDrawPoint(m_renderer, centerX - x, centerY + y);
		SDL_RenderDrawPoint(m_renderer, centerX + y, centerY - x);
		SDL_RenderDrawPoint(m_renderer, centerX + y, centerY + x);
		SDL_RenderDrawPoint(m_renderer, centerX - y, centerY - x);
		SDL_RenderDrawPoint(m_renderer, centerX - y, centerY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void vic::Renderer::RenderRect(float left, float top, float width, float height, SDL_Color color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	const SDL_Rect drawRect{ static_cast<int>(left), static_cast<int>(top), static_cast<int>(width), static_cast<int>(height) };
	SDL_RenderDrawRect(m_renderer, &drawRect);
}

void vic::Renderer::FillCircle(float x, float y, float radius, SDL_Color color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			float dx = radius - w; // horizontal offset
			float dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(m_renderer, static_cast<int>(x + dx), static_cast<int>(y + dy));
			}
		}
	}
}

SDL_Renderer* vic::Renderer::GetSDLRenderer() const { return m_renderer; }

void vic::Renderer::SetDrawColor(int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(m_renderer, static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b), static_cast<uint8_t>(a));
}
