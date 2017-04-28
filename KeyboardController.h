#pragma once

#include "KeyEventHandler.h"
#include "ControllableObject.h"

namespace game
{
	class KeyboardController: public KeyEventHandler
	{	
		ControllableObject* target_;

	public:
		KeyboardController(Application& parent, ControllableObject* target);

		void setMovementKey(WKey key, MovementFlag::Type movement);
	};
}
