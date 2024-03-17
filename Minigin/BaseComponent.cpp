#include "BaseComponent.h"

void minigin::BaseComponent::AddCommand(std::unique_ptr<BaseCommand>&& baseCommand)
{
	m_Commands.emplace_back(std::move(baseCommand));
}

minigin::BaseComponent::BaseComponent(GameObject* ownerPtr):
	m_OwnerPtr{ownerPtr}
{
}
