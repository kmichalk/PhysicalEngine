#pragma once

#include "ApplicationComponent.h"
#include "Clearable.h"
#include "xvector.h"
#include "Handler.h"


namespace game
{
	class Task;

	class TaskHandler: 
		public Handler<Task>, public ApplicationComponent, virtual public Clearable
	{
		G_OBJECT;
	public:
		TaskHandler(Application& parent);

		virtual void process() override;
		size_t activeTasksNumber() const;

		virtual ~TaskHandler();
	};
}

