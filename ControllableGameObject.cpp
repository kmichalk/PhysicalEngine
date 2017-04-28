#include "ControllableGameObject.h"

namespace game
{
	ControllableGameObject::ControllableGameObject(GameObject const & other):
		GameObject(other)
	{
	}

	void ControllableGameObject::refresh()
	{
		GameObject::refresh();
		physicalObject_->dynamics.velocity = getMoveDirection()*3.0;
	}
}