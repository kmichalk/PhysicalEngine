#include "KeyHoldEvent.h"


namespace game
{
	KeyHoldEvent::KeyHoldEvent(WKey key, double period, Procedure * onHold):
		KeyEvent(key, nullptr, nullptr),
		period_{period},
		onHold_{onHold}
	{
	}

	KeyHoldEvent::KeyHoldEvent(
		WKey key, double period, Procedure * onPress, Procedure * onRelease, Procedure * onHold):
		KeyEvent(key, onPress, onRelease),
		period_{period},
		onHold_{onHold}
	{
	}

	KeyHoldEvent::KeyHoldEvent(KeyHoldEvent const & other):
		KeyEvent(other),
		period_{other.period_},
		onHold_{other.onHold_->copy()}
	{
	}

	KeyHoldEvent::KeyHoldEvent(KeyHoldEvent && other):
		KeyEvent(other),
		period_{other.period_},
		onHold_{other.onHold_}
	{
	}

	Procedure* KeyHoldEvent::triggered_()
	{
		bool previous = pressed_;
		if ((pressed_ = isPressed(keys_[0])) == previous) {
			return period_.reached() ?
				period_.start(), onHold_ :
				nullptr;
		}
		else {
			if (pressed_) {
				period_.start();
				return onPress_;
			}
			return onRelease_;
		}
	}


}