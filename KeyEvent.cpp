#include "KeyEvent.h"


namespace game
{
	Procedure* KeyEvent::triggered_()
	{
		bool previous = pressed_;
		if ((pressed_ = isPressed(keys_[0])) != previous) 
			return pressed_ ? onPress_ : onRelease_;
		return nullptr;
	}

	KeyEvent::KeyEvent(x::vector<WKey> const & keys, Procedure * onPress, Procedure * onRelease):
		Event(Type::KEY_EVENT),
		pressed_{false},
		keys_{keys},
		onPress_{onPress},
		onRelease_{onRelease}
	{
	}

	KeyEvent::KeyEvent(WKey key, Procedure * onPress, Procedure * onRelease):
		Event(Type::KEY_EVENT),
		pressed_{false},
		keys_{key},
		onPress_{onPress},
		onRelease_{onRelease}
	{
	}
	//
	//KeyEvent::KeyEvent(x::vector<WKey> const & keys, Procedure * onPress, Procedure * onRelease):
	//	pressed_{false},
	//	keys_{keys},
	//	onPress_{onPress},
	//	onRelease_{onRelease}
	//{
	//}

	KeyEvent::KeyEvent(KeyEvent const & other):
		Event(Type::KEY_EVENT),
		pressed_{false},
		keys_{other.keys_},
		onPress_{other.onPress_->copy()},
		onRelease_{other.onRelease_->copy()}
	{
	}

	KeyEvent::KeyEvent(KeyEvent && other):
		Event(Type::KEY_EVENT),
		pressed_{false},
		keys_{other.keys_.move()},
		onPress_{other.onPress_},
		onRelease_{other.onRelease_}
	{
	}

	/*KeyEvent * KeyEvent::copy() const
	{
		return new KeyEvent{*this};
	}*/

	KeyEvent::~KeyEvent()
	{
		if (onPress_)
			delete onPress_;
		if (onRelease_)
			delete onRelease_;
	}

	void KeyEvent::setOnPress(Procedure * onPress)
	{
		onPress_ = onPress;
	}

	void KeyEvent::setOnRelease(Procedure * onRelease)
	{
		onRelease_ = onRelease;
	}

	WKey KeyEvent::getPrimaryKey() const
	{
		return keys_[0];
	}

	KeyPressEvent::KeyPressEvent(WKey key, Procedure * onPress):
		KeyEvent(key, onPress, nullptr)
	{
	}

	KeyReleaseEvent::KeyReleaseEvent(WKey key, Procedure * onRelease) :
		KeyEvent(key, nullptr, onRelease)
	{
	}
}