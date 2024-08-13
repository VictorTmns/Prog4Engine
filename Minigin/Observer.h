﻿#pragma once
#include <vector>

namespace vic
{
	class BaseComponent;


	class Observer
	{
	public:
		enum class Event
		{
			subjectAttached,
			subjectDestroyed,

			scoreChange,
			playerHealthChanges,
			enemyDied,
			respawn,

		};
	
		virtual ~Observer();
		virtual void Notify(Event event, const BaseComponent* subject) = 0;

		void AddSubject(BaseComponent* subject);
	private:
		std::vector<BaseComponent*> m_Subjects;
	};
}
