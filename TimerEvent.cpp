#include "TimerEvent.h"

namespace game
{
	TimerEvent::TimerEvent(Procedure * action, double period, bool looped):
		Event(Type::TIMER_EVENT, nullptr),
		TimePeriod(period),
		looped_{looped},
		action_{action}
	{
	}

	TimerEvent::TimerEvent(TaskHandler * handler, Procedure * action, double period, bool looped):
		Event(Type::TIMER_EVENT, handler),
		TimePeriod(period),
		looped_{looped},
		action_{action}
	{
	}

	Procedure* TimerEvent::triggered_()
	{
		if (isEnabled() && reached()) {
			if (looped_)
				this->start();
			else
				setEnabled(false);
			return action_;
		}
		return nullptr;
	}
}