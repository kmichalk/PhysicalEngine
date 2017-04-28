#include "MainThread.h"

namespace game
{
	MainThread::MainThread()
	{
	}


	void MainThread::run()
	{
		prepare();
		runSubthreads_();
		performLoop_();
	}
}
