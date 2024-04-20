#include "TextureRenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"


void minigin::TextureRenderComponent::Render() const
{
	const glm::vec2 pos = GetOwner()->GetWorldTransform().GetPosition();

	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void minigin::TextureRenderComponent::SetTexture(const std::string& texturePath)
{
	m_Texture = ResourceManager::GetInstance().GetTexture(texturePath);
}
