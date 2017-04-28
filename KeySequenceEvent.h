#pragma once

#include "KeyEvent.h"


namespace game
{
	class KeySequenceEvent: public KeyEvent
	{
		G_OBJECT;
	protected:
		x::vector<WKey>::const_iterator last_;

		virtual Procedure* triggered_() override;

	public:
		KeySequenceEvent(x::vector<WKey> const& sequence, Procedure* onFinish, Procedure* onFail = nullptr);
		KeySequenceEvent(KeySequenceEvent const& other);
		KeySequenceEvent(KeySequenceEvent && other);
	};
}