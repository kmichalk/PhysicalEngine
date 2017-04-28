#include "KeySequenceEvent.h"

namespace game
{
	Procedure* KeySequenceEvent::triggered_()
	{
		bool previous = pressed_;
		if ((pressed_ = isPressed(*last_)) != previous && pressed_) {
			if (!(++last_)) {
				last_ = keys_.cbegin();
				return onPress_;
			}
		}
		return nullptr;
	}

	KeySequenceEvent::KeySequenceEvent(x::vector<WKey> const & sequence, Procedure * onFinish, Procedure * onFail):
		KeyEvent(sequence, onFinish, onFail),
		last_{keys_.cbegin()}
	{
	}

	KeySequenceEvent::KeySequenceEvent(KeySequenceEvent const & other):
		KeyEvent(other),
		last_{keys_.cbegin()}
	{
	}

	KeySequenceEvent::KeySequenceEvent(KeySequenceEvent && other):
		KeyEvent(other),
		last_{keys_.cbegin()}
	{
	}
}