#include "ThrashTheCacheComponent.h"

#include <chrono>

#include "../3rdParty/imgui-1.90.4/imgui.h"
#include "../3rdParty/imgui-1.90.4/backends/imgui_impl_opengl3.h"
#include "../3rdParty/imgui-1.90.4/backends/imgui_impl_sdl2.h"
#include "../3rdParty/imgui-1.90.4/imgui_plot.h"


ThrashTheCacheComponent::ThrashTheCacheComponent(vic::GameObject* parentPtr) :
	BaseComponent{parentPtr}
{
}

void ThrashTheCacheComponent::Update()
{
	static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), };


	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::InputInt("sampleSize", &m_SampleSize);
	if (ImGui::Button("Trash the cache with GameObject3D"))
		Calculate3DGameobjectData();

	if (!m_3DGameObjectData.empty())
	{
		ImGui::PlotConfig conf{};
		//conf.values.xs = x_data; // this line is optional
		conf.values.color = colors[0];
		conf.values.ys = m_3DGameObjectData.data();
		conf.values.count = static_cast<int>(m_3DGameObjectData.size());
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = false;
		conf.frame_size = ImVec2(200, 150);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}



	if (ImGui::Button("Trash the cache with AltGameObject3D"))
		CalculateAlt3DGameobjectData();

	if (!m_Alt3DGameObjectData.empty())
	{
		ImGui::PlotConfig conf{};
		//conf.values.xs = x_data; // this line is optional
		conf.values.color = colors[1];
		conf.values.ys = m_Alt3DGameObjectData.data();
		conf.values.count = static_cast<int>(m_Alt3DGameObjectData.size());
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = false;
		conf.frame_size = ImVec2(200, 150);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}

	if (!m_Alt3DGameObjectData.empty() && !m_3DGameObjectData.empty())
	{
		const float* y_data[] = { m_3DGameObjectData.data(), m_Alt3DGameObjectData.data() };
		ImGui::PlotConfig conf{};
		conf.values.ys_list = y_data;
		conf.values.ys_count = 2;
		conf.values.count = static_cast<int>(m_3DGameObjectData.size());
		conf.values.colors = colors;
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = false;
		conf.frame_size = ImVec2(200, 150);
		conf.line_thickness = 2.f;


		ImGui::Plot("plot", conf);
	}
	ImGui::End();

}


void ThrashTheCacheComponent::Calculate3DGameobjectData()
{
	std::vector<GameObject3D> arr(static_cast<size_t>(powf(2.f, 26.f)));

	for (int power = 0; power <= 10; power++)
	{
		float totalTime{};
		int stepsize{ static_cast<int>(powf(2, float(power))) };
		for (int j = 0; j < m_SampleSize; ++j)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < static_cast<int>(arr.size()); i += stepsize)
			{
				arr[i].id *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<float> duration = end - start;

			totalTime += duration.count();
		}
		m_3DGameObjectData.push_back(totalTime / static_cast<float>(m_SampleSize));

	}
}

void ThrashTheCacheComponent::CalculateAlt3DGameobjectData()
{

	std::vector<GameObject3DAlt> arr(static_cast<size_t>(powf(2.f, 26.f)));

	for (int power = 0; power <= 10; power++)
	{
		float totalTime{};
		int stepsize{ static_cast<int>(powf(2, float(power))) };
		for (int j = 0; j < m_SampleSize; ++j)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < static_cast<int>(arr.size()); i += stepsize)
			{
				arr[i].id *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<float> duration = end - start;

			totalTime += duration.count();
		}
		m_Alt3DGameObjectData.push_back(totalTime / static_cast<float>(m_SampleSize));

	}
}
