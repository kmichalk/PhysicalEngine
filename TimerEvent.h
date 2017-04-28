#pragma once

#include "Event.h"
#include "TimePeriod.h"

namespace game
{

	class TimerEvent: public Event, protected TimePeriod
	{
		G_OBJECT;

		volatile bool looped_;
		Procedure* action_;

		virtual Procedure* triggered_() override;

	public:
		TimerEvent(
			Procedure* action,
			double	period,
			bool looped = false);

		TimerEvent(
			game::TaskHandler* handler,
			Procedure* action,
			double	period,
			bool looped = false);

	};
}