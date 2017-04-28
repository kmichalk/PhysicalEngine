#include "IterativeTaskHandler.h"
#include "Task.h"


namespace game
{
	void IterativeTaskHandler::process()
	{
		foreach(p, reliants_) {
			p->process();
		}
	}

}
