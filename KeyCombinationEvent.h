#pragma once

#include "KeyEvent.h"

namespace game
{
	class KeyCombinationEvent: public KeyEvent
	{
		G_OBJECT;
	protected:
		virtual Procedure* triggered_() override;

	public:
		KeyCombinationEvent(x::vector<WKey> const& keys, Procedure* onPress, Procedure* onRelease = nullptr);
		KeyCombinationEvent(KeyCombinationEvent const& other);
		KeyCombinationEvent(KeyCombinationEvent && other);

		//virtual KeyCombinationEvent* copy() const override;
	};
}