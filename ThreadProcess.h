#pragma once

#include "Thread.h"
#include "Reliant.h"
#include "Clearable.h"

namespace game
{
	class ProcessHandler;

	class ThreadProcess: 
		public Thread, public Reliant<ThreadProcess>, virtual public Clearable
	{
		G_OBJECT;
	protected:
		void performLoop_();

		volatile bool stopped_;
		//volatile bool paused_;
		unsigned resumeCheckPeriod_;

	public:
		static constexpr unsigned DEFAULT_RESUME_CHECK_PERIOD = 20;

		ThreadProcess(ProcessHandler* handler = nullptr);

		virtual void run() override;
		virtual void process() abstract override;
		virtual void clear() override;
		virtual void stop();
		virtual bool hasStopped() const;
		virtual void pause(unsigned resumeCheckTime = DEFAULT_RESUME_CHECK_PERIOD);
		virtual void resume();
		virtual void prepare();
		bool isPaused() const;

		virtual ~ThreadProcess();
	};

	///////////////////////////////////////////////////////////////////////////////

	inline bool ThreadProcess::isPaused() const
	{
		return isEnabled();
	}
}
