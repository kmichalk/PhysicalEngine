#include "Thread.h"
#include <processthreadsapi.h>


namespace game
{
	Thread::Thread():
		thread_{nullptr},
		running_{false}
	{
	}

	void Thread::run() throw(x::error<Thread>)
	{
		running_ = true;
		executeAsThread_(&Thread::process, this);
		running_ = false;
	}


	void Thread::terminate()
	{
		if (thread_) {
			delete thread_;
			running_ = false;
		}
	}

	void Thread::join()
	{
		if (thread_ && thread_->joinable())
			thread_->join();
	}

	bool Thread::isRunning() const
	{
		return thread_ && running_;
	}


	unsigned long Thread::getId() const
	{
		if (thread_)
			return GetCurrentThreadId();
		else
			return 0;
	}

	Thread::~Thread()
	{
		if (thread_) {
			thread_->join();
		}
	}
}