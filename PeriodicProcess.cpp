#include "PeriodicProcess.h"

namespace game
{
	void PeriodicProcess::performLoop_()
	{
		prepare();
		unsigned long sleepTime = 0;
		stopped_ = false;
		running_ = true;
		setEnabled(true);

		periodTimer_.tic();
		while (running_) {
			//lastProcessTime_ = periodTimer_.measure();
			if (isEnabled()) {
				if (waitType_ == WaitType::SLEEP) {
					processIfSleepWait_();
				}
				else if (waitType_ == WaitType::ACTIVE) {
					processIfActiveWait_();
				}				
			}
			else
				Sleep(resumeCheckPeriod_);
		}
		stopped_ = true;
	}

	void PeriodicProcess::processIfActiveWait_()
	{
		if (periodTimer_.measure() > period_) {
			process();
		}
	}

	void PeriodicProcess::processIfSleepWait_()
	{
		periodTimer_.tic();
		process();
		//lastProcessTime_ = periodTimer_.toc();
		//sleepTime = x::cutl((period_ - lastProcessTime_) * 1000);
		//sleep_(sleepTime);
		sleep_((period_ - periodTimer_.toc()) * 1000);
	}

	void PeriodicProcess::sleep_(long time) const
	{
		if (time >= minSleepTime_)
			Sleep((DWORD)time);
	}

	PeriodicProcess::PeriodicProcess(double period):
		PeriodicProcess(nullptr, period)
	{
	}

	PeriodicProcess::PeriodicProcess(ProcessHandler * handler, double period):
		ThreadProcess(handler),
		periodTimer_{},
		period_{period},
		lastProcessTime_{0},
		minSleepTime_{DEFAULT_MINIMAL_SLEEP_TIME},
		waitType_{DEFAULT_WAIT_TYPE}
	{
	}

	void PeriodicProcess::run()
	{
		executeAsThread_(&PeriodicProcess::performLoop_, this);
	}

	//void PeriodicProcess::pause(unsigned resumeCheckTime)
	//{
	//	ThreadProcess::pause(resumeCheckTime);
	//}

	void PeriodicProcess::resume()
	{
		periodTimer_.tic();
		ThreadProcess::resume();
	}

	void PeriodicProcess::setPeriod(double period)
	{
		if (period >= MINIMAL_PROCESS_PERIOD)
			period_ = period;
	}

	double PeriodicProcess::getPeriod() const
	{
		return period_;
	}

	double PeriodicProcess::lastProcessTime() const
	{
		return lastProcessTime_;
	}

	void PeriodicProcess::setWaitType(WaitType type)
	{
		waitType_ = type;
	}

	void PeriodicProcess::setMinSleepTime(double time)
	{
		if (time > 0.001)
			minSleepTime_ = (long)(time * 1000);
	}

}
