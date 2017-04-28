#include "ProcessHandler.h"

namespace game
{
	void ProcessHandler::run()
	{
		runSubthreads_();
		ThreadProcess::run();
	}


	void ProcessHandler::runSubthreads_()
	{
		foreach(t, reliants_) {
			try {
				t->run();
			}
			catch (x::error<Thread> e) {
				std::cout << e.message();
			}
		}
	}

	void ProcessHandler::stop()
	{
		foreach(t, reliants_)
			t->stop();
		ThreadProcess::stop();
	}


	void ProcessHandler::pause(unsigned resumeCheckTime)
	{
		foreach(t, reliants_)
			t->pause(resumeCheckTime);
		ThreadProcess::pause(resumeCheckTime);
	}


	void ProcessHandler::resume()
	{
		foreach(t, reliants_)
			t->resume();
		ThreadProcess::resume();
	}


	void ProcessHandler::terminate()
	{
		foreach(t, reliants_)
			t->terminate();
		ThreadProcess::terminate();
	}


	void ProcessHandler::join()
	{
		foreach(t, reliants_)
			t->join();
		ThreadProcess::join();
	}

	bool ProcessHandler::hasStopped() const
	{
		return reliants_.true_for_all([](ThreadProcess* p) {return p->hasStopped(); });
	}
}
