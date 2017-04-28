#pragma once

#include "ThreadProcess.h"
#include "Timer.h"


namespace game
{
	class PeriodicProcess: public ThreadProcess
	{
		G_OBJECT;
	public:
		enum class WaitType: byte
		{
			SLEEP, ACTIVE
		};

	private:
		Timer periodTimer_;
		double period_;
		double lastProcessTime_;
		long minSleepTime_;
		WaitType waitType_;

		void performLoop_();
		void processIfActiveWait_();
		void processIfSleepWait_();
		void sleep_(long time) const;

	public:
		static constexpr double DEFAULT_PROCESS_PERIOD = 0.05;
		static constexpr double MINIMAL_PROCESS_PERIOD = 0.01;
		static constexpr unsigned long DEFAULT_MINIMAL_SLEEP_TIME = 10;
		static constexpr WaitType DEFAULT_WAIT_TYPE = WaitType::SLEEP;

		PeriodicProcess(double period = DEFAULT_PROCESS_PERIOD);
		PeriodicProcess(ProcessHandler* handler, double period = DEFAULT_PROCESS_PERIOD);

		virtual void run() override;
		//virtual void pause(unsigned resumeCheckTime = DEFAULT_RESUME_CHECK_PERIOD) override;
		virtual void resume() override;
		void setPeriod(double period);
		double getPeriod() const;
		double lastProcessTime() const;
		void setWaitType(WaitType type);
		void setMinSleepTime(double time);
	};
}

