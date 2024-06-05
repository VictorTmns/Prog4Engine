#include "BaseComponent.h"

#include <assert.h>

#include "Observer.h"


void vic::BaseComponent::AddCommand(std::unique_ptr<BaseCommand>&& baseCommand)
{
	m_Commands.emplace_back(std::move(baseCommand));
}
void vic::BaseComponent::AttachObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
	observer->Notify(Observer::Event::subjectAttached, this);
}
void vic::BaseComponent::RemoveObserver(Observer* observerToRemove)
{
	std::erase_if(
		m_Observers,
		[observerToRemove](Observer* observer) {return observer == observerToRemove; }
	);
}

vic::BaseComponent::BaseComponent(GameObject* ownerPtr):
	m_OwnerPtr{ownerPtr}
{
	assert(ownerPtr != nullptr);
}

void vic::BaseComponent::NotifyObservers(Observer::Event event) const
{
	for (Observer* observer : m_Observers)
	{
		observer->Notify(event, this);
	}
}
