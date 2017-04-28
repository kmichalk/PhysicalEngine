#pragma once

#include "Processable.h"
//#include "Clearable.h"
#include "Reliant.h"


namespace game
{
	class TaskHandler;


	class Task:
		public Reliant<Task>, virtual public Processable
	{
		G_OBJECT;

	public:
		Task(TaskHandler* handler = nullptr);

		virtual void process() abstract override;
		//virtual void clear() abstract override;
	};
}