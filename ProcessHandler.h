#pragma once

#include "ThreadProcess.h"
#include "Handler.h"


namespace game
{
	class ProcessHandler: public Handler<ThreadProcess>
	{
		G_OBJECT;
	protected:
		void runSubthreads_();

	public:
		virtual void process() abstract override;
		virtual void run() override;
		virtual void stop() override;
		virtual void pause(unsigned resumeCheckTime = DEFAULT_RESUME_CHECK_PERIOD) override;
		virtual void resume() override;
		virtual void terminate() override;
		virtual void join() override;
		virtual bool hasStopped() const override;
	};
}
