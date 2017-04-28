#include "TaskHandler.h"
#include "Process.h"
#include "Task.h"


namespace game
{
	TaskHandler::TaskHandler(Application & parent):
		Handler<Task>(),
		ApplicationComponent(parent)
	{
	}

	void TaskHandler::process()
	{
		if (isEnabled()) {
			foreach(t, reliants_){
				if (t->isEnabled())
					t->process();
			}
		}
	}

	size_t TaskHandler::activeTasksNumber() const
	{
		return reliants_.count_if([](auto t) {return t->isEnabled(); });
	}

	TaskHandler::~TaskHandler()
	{
		clear();
	}
}

