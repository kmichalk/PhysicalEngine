#include "Mouse.h"
#include "SFML\Graphics.hpp"
#include "Application.h"
#include "crd_cast.h"

namespace game
{
	Mouse::Mouse()
		:
		Element{MOUSE_TYPE_PROPERTIES_}
	{
	}

	Point Mouse::getPosition() const
	{
		try {
			return enginePtr_->realPos(appPtr_->get.mousePosition());
		}
		catch (x::error<game::DrawingHandler>) { std::cout<<"no window\n"; }
	}
	x::Abstract<Value<Point>> Mouse::positionReference()
	{
		return Value<Point>::createMember(this, &Mouse::getPosition);
	}
}