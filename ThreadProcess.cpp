#include "ThreadProcess.h"
#include "ProcessHandler.h"


namespace game
{
	void ThreadProcess::performLoop_()
	{
		running_ = true;
		stopped_ = false;
		setEnabled(true);
		while (running_) {
			if (isEnabled())
				process();
			else
				Sleep(resumeCheckPeriod_);
		}
		stopped_ = true;
	}

	ThreadProcess::ThreadProcess(ProcessHandler * handler):
		Reliant<ThreadProcess>(handler),
		stopped_{false},
		resumeCheckPeriod_{DEFAULT_RESUME_CHECK_PERIOD}
	{
	}

	void ThreadProcess::run()
	{		
		executeAsThread_(&ThreadProcess::performLoop_, this);
	}

	void ThreadProcess::clear()
	{
	}

	void ThreadProcess::stop()
	{
		running_ = false;
	}

	bool ThreadProcess::hasStopped() const
	{
		return stopped_;
	}

	void ThreadProcess::pause(unsigned resumeCheckPeriod)
	{
		resumeCheckPeriod_ = resumeCheckPeriod;
		setEnabled(false);
	}

	void ThreadProcess::resume()
	{
		setEnabled(true);
	}

	void ThreadProcess::prepare()
	{
	}

	ThreadProcess::~ThreadProcess()
	{
		stop(); 
		join();
		clear();
	}

}