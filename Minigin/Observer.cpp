#include "Observer.h"
#include "BaseComponent.h"


minigin::Observer::~Observer()
{
	for (BaseComponent* subject : m_Subjects)
	{
		subject->RemoveObserver(this);
	}
}

void minigin::Observer::AddSubject(BaseComponent* subject)
{
	m_Subjects.emplace_back(subject);
}
