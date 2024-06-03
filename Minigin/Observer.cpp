#include "Observer.h"
#include "BaseComponent.h"


vic::Observer::~Observer()
{
	for (BaseComponent* subject : m_Subjects)
	{
		subject->RemoveObserver(this);
	}
}

void vic::Observer::AddSubject(BaseComponent* subject)
{
	m_Subjects.emplace_back(subject);
}
