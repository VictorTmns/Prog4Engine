#include "BaseComponent.h"

#include "Observer.h"


void minigin::BaseComponent::AddCommand(std::unique_ptr<BaseCommand>&& baseCommand)
{
	m_Commands.emplace_back(std::move(baseCommand));
}
void minigin::BaseComponent::AttachObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
	observer->Notify(Observer::Event::subjectAttached, this);
}
void minigin::BaseComponent::RemoveObserver(Observer* observerToRemove)
{
	std::erase_if(
		m_Observers,
		[observerToRemove](Observer* observer) {return observer == observerToRemove; }
	);
}

minigin::BaseComponent::BaseComponent(GameObject* ownerPtr):
	m_OwnerPtr{ownerPtr}
{
}

void minigin::BaseComponent::NotifyObservers(Observer::Event event) const
{
	for (Observer* observer : m_Observers)
	{
		observer->Notify(event, this);
	}
}
