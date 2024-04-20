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

		TextureRenderComponent(GameObject* owner) : BaseComponent{owner} {}
	private:
		Texture2D* m_Texture{};
	};
}