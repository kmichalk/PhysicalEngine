#include "Task.h"
#include "TaskHandler.h"


namespace game
{
	Task::Task(TaskHandler * handler):
		Reliant<Task>(handler)
	{
	}
}
