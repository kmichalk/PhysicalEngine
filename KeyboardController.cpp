#include "KeyboardController.h"

namespace game
{
	KeyboardController::KeyboardController(Application& parent, ControllableObject * target):
		KeyEventHandler(parent),
		target_{target}
	{
	}

	void KeyboardController::setMovementKey(WKey key, MovementFlag::Type movement)
	{
		MovementFlag& flag = target_->selectMovementFlag(movement);
		addReliant(new KeyEvent{key,
			new Function<void()>{[&flag] {flag.setEnabled(true); }},
			new Function<void()>{[&flag] {flag.setEnabled(false); }}});
	}
}