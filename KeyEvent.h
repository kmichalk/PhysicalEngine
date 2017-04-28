#pragma once

#include "Event.h"
#include "wkey.h"
#include "xvector.h"

#undef KEY_EVENT

namespace game
{
	class KeyEvent: public Event
	{
		G_OBJECT;
	protected:
		bool pressed_;
		x::vector<WKey> keys_;

		Procedure* onPress_;
		Procedure* onRelease_;

		virtual Procedure* triggered_() override;

		KeyEvent(x::vector<WKey> const& keys, Procedure* onPress, Procedure* onRelease = nullptr);

	public:
		KeyEvent(WKey key, Procedure* onPress, Procedure* onRelease = nullptr);
		KeyEvent(KeyEvent const& other);
		KeyEvent(KeyEvent&& other);

		//virtual KeyEvent* copy() const override;
		virtual ~KeyEvent();

		void setOnPress(Procedure* onPress);
		void setOnRelease(Procedure* onRelease);
		WKey getPrimaryKey() const;
	};

	///////////////////////////////////////////////////////////////////////////////

	class KeyPressEvent: public KeyEvent
	{
		G_OBJECT;
	public:
		KeyPressEvent(WKey key, Procedure* onPress);
	};

	///////////////////////////////////////////////////////////////////////////////

	class KeyReleaseEvent: public KeyEvent
	{
		G_OBJECT;
	public:
		KeyReleaseEvent(WKey key, Procedure* onRelease);
	};
}