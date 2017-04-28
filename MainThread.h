#pragma once

#include "Thread.h"
#include "ProcessHandler.h"


namespace game
{
	class MainThread: virtual public ProcessHandler
	{	
		G_OBJECT;
	public:
		MainThread();

		virtual void process() abstract override;
		virtual void run() override;
	};
}
