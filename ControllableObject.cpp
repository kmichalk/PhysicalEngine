#include "ControllableObject.h"
#include "bitliteral.h"
#include "KeyboardController.h"

namespace game
{
	ControllableObject::ControllableObject():
		controller_{nullptr},
		movingUp{MovementFlag::Type::UP},
		movingDown{MovementFlag::Type::DOWN},
		movingLeft{MovementFlag::Type::LEFT},
		movingRight{MovementFlag::Type::RIGHT}
	{
	}

	ControllableObject::ControllableObject(KeyboardController* controller):
		controller_{controller},
		movingUp{MovementFlag::Type::UP},
		movingDown{MovementFlag::Type::DOWN},
		movingLeft{MovementFlag::Type::LEFT},
		movingRight{MovementFlag::Type::RIGHT}
	{
	}


	MovementFlag & ControllableObject::selectMovementFlag(MovementFlag::Type type)
	{
		return this->*FLAG_MAP_[(byte)type];
	}

	Vector ControllableObject::getMoveDirection() const
	{
		return MovementFlag::sumDirections(
			movingUp.isEnabled(),
			movingDown.isEnabled(),
			movingLeft.isEnabled(),
			movingRight.isEnabled()
		);
		/*Vector result{0.0, 0.0};
		byte requiresNormalization = 0;
		if (movingUp.isEnabled()) {
			result += movingUp.direction;
			requiresNormalization |= x::BIT<0>;
		}
		if (movingDown.isEnabled()) {
			result += movingDown.direction;
			requiresNormalization |= x::BIT<0>;
		}
		if (movingLeft.isEnabled()) {
			result += movingLeft.direction;
			requiresNormalization |= x::BIT<1>;
		}
		if (movingRight.isEnabled()) {
			result += movingRight.direction;
			requiresNormalization |= x::BIT<1>;
		}

		return requiresNormalization ? result.normalize() : result;*/
	}

	KeyboardController * ControllableObject::getController() const
	{
		return controller_;
	}

	ControllableObject::FlagMember ControllableObject::FLAG_MAP_[4] = {
		&ControllableObject::movingUp,
		&ControllableObject::movingDown,
		&ControllableObject::movingLeft,
		&ControllableObject::movingRight
	};
}