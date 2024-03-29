#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "../3rdParty/imgui-1.90.4/imgui.h"
#include "../3rdParty/imgui-1.90.4/backends/imgui_impl_opengl3.h"
#include "../3rdParty/imgui-1.90.4/backends/imgui_impl_sdl2.h"

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

void minigin::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

}


void minigin::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);



	SceneManager::GetInstance().Render();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

}

void minigin::Renderer::Destroy()
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

void minigin::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void minigin::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}


void minigin::Renderer::RenderCircle(float xCenter, float yCenter, float radius, SDL_Color color)
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

void minigin::Renderer::RenderRect(float left, float top, float width, float height, SDL_Color color)
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

	const SDL_Rect drawRect{ static_cast<int>(left), static_cast<int>(top), static_cast<int>(width), static_cast<int>(height) };
	SDL_RenderDrawRect(m_renderer, &drawRect);
}

void minigin::Renderer::FillCircle(float x, float y, float radius, SDL_Color color)
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

SDL_Renderer* minigin::Renderer::GetSDLRenderer() const { return m_renderer; }
