#pragma once

#include "Locatable.h"
#include "Object.h"
#include "MovementFlag.h"

namespace game
{
	class KeyboardController;

	class ControllableObject: virtual public Object
	{
		G_OBJECT;

	protected:

	public:
		KeyboardController* controller_;

		MovementFlag movingUp;
		MovementFlag movingDown;
		MovementFlag movingLeft;
		MovementFlag movingRight;

		ControllableObject();
		ControllableObject(KeyboardController* controller);

		MovementFlag& selectMovementFlag(MovementFlag::Type type);
		Vector getMoveDirection() const;
		KeyboardController* getController() const;

	private:
		using FlagMember = MovementFlag(ControllableObject::*);

		static FlagMember FLAG_MAP_[4];
	};
}
