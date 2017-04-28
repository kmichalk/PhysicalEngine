#pragma once

#include <thread>
#include <atomic>
#include "error.h"
#include "id.h"
#include "Processable.h"
#include "Object.h"


namespace game
{
	class Thread: virtual public Object, virtual public Processable
	{
		G_OBJECT;

		std::thread* thread_;

	protected:
		volatile bool running_;

		Thread();

		template<class _Func>
		void executeAsThread_(_Func&& func) throw(x::error<Thread>);

		template<class _Memb, class _Owner>
		void executeAsThread_(_Memb&& func, _Owner&& owner) throw(x::error<Thread>);

	public:
		virtual void run() throw(x::error<Thread>);
		virtual void process() abstract override;
		//virtual void stop() abstract;
		virtual void terminate();
		virtual void join();
		bool isRunning() const;
		unsigned long getId() const;

		virtual ~Thread();
	};

	///////////////////////////////////////////////////////////////////////////////

	template<class _Func>
	inline void Thread::executeAsThread_(_Func && func) throw(x::error<Thread>)
	{
		if (!thread_) {
			thread_ = new std::thread(func);
		}
		else
			throw x::error<Thread>{"Thread already initialized"};
	}

	template<class _Memb, class _Owner>
	inline void Thread::executeAsThread_(_Memb && func, _Owner && owner) throw(x::error<Thread>)
	{
		if (!thread_) {
			thread_ = new std::thread(func, x::pointer(owner));
		}
		else
			throw x::error<Thread>{"Thread already initialized"};
	}

}
