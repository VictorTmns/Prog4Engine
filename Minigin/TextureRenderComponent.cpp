#include "TextureRenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"


void vic::TextureRenderComponent::Render(const Renderer* renderer) const
{
	const glm::vec2 pos = GetOwner()->GetTransform().Position();

	m_Texture->Draw(renderer, pos.x, pos.y);
}

void vic::TextureRenderComponent::SetTexture(const std::string& texturePath)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(texturePath);
}
