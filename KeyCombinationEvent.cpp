#include "KeyCombinationEvent.h"


namespace game
{
	Procedure* KeyCombinationEvent::triggered_()
	{
		bool previous = pressed_;
		foreach(k, keys_)
			if (!isPressed(*k)) {
				pressed_ = false;
				return previous ? onRelease_ : nullptr;
			}
		pressed_ = true;
		return onPress_;
	}

	KeyCombinationEvent::KeyCombinationEvent(x::vector<WKey> const & keys, Procedure * onPress, Procedure * onRelease):
		KeyEvent(keys, onPress, onRelease)
	{
	}

	KeyCombinationEvent::KeyCombinationEvent(KeyCombinationEvent const & other) :
		KeyEvent(other)
	{
	}

	KeyCombinationEvent::KeyCombinationEvent(KeyCombinationEvent && other) :
		KeyEvent(other)
	{
	}

	/*KeyCombinationEvent * KeyCombinationEvent::copy() const
	{
		return new KeyCombinationEvent{*this};
	}*/
}