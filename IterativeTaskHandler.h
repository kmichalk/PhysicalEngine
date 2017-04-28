#pragma once

#include "TaskHandler.h"


namespace game
{
	class IterativeTaskHandler: public TaskHandler
	{
	public:
		virtual void process() override;
	};
}
