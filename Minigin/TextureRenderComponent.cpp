#include "TextureRenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"


void minigin::TextureRenderComponent::Render(const Renderer* renderer) const
{
	const glm::vec2 pos = GetOwner()->GetWorldTransform().GetPosition();

	m_Texture->Draw(renderer, pos.x, pos.y);
}

void minigin::TextureRenderComponent::SetTexture(const std::string& texturePath)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(texturePath);
}
