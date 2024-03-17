#pragma once
#include <memory>
#include <string>

#include "BaseComponent.h"
#include "Texture2D.h"
#include "Transform.h"

namespace minigin
{
	class TextureRenderComponent : public BaseComponent
	{
	public:

		void Render() const override;

		void SetTexture(const std::string& texturePath);
		void SetOffset(float x, float y);

		TextureRenderComponent(GameObject* owner) : BaseComponent{owner} {};
		virtual ~TextureRenderComponent() = default;
		TextureRenderComponent(const TextureRenderComponent& other) = delete;
		TextureRenderComponent(TextureRenderComponent&& other) = delete;
		TextureRenderComponent& operator=(const TextureRenderComponent& other) = delete;
		TextureRenderComponent& operator=(TextureRenderComponent&& other) = delete;
	private:
		minigin::Transform m_Offset{};
		Texture2D* m_Texture{};
	};
}