#pragma once

#include "KeyEvent.h"
#include "TimePeriod.h"


namespace game
{
	class KeyHoldEvent: public KeyEvent
	{
		G_OBJECT;

		TimePeriod period_;

	protected:
		Procedure* onHold_;
		virtual Procedure* triggered_() override;

	public:
		KeyHoldEvent(WKey key, double period, Procedure* onHold);
		KeyHoldEvent(WKey key, double period, Procedure* onPress, Procedure* onRelease, Procedure* onHold);
		KeyHoldEvent(KeyHoldEvent const& other);
		KeyHoldEvent(KeyHoldEvent && other);
	};
}