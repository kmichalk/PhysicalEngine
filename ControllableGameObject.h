#pragma once

#include "GameObject.h"
#include "ControllableObject.h"


namespace game
{
	class ControllableGameObject: public GameObject, public ControllableObject
	{
		G_OBJECT;

	public:
		using GameObject::GameObject;
		ControllableGameObject(GameObject const& other);

		virtual void refresh() override;
	};
}
