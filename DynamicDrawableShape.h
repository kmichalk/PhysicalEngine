#pragma once

#include "DrawableShape.h"

namespace game
{
	class DynamicDrawableShape: public DrawableShape
	{
	public:
		DynamicDrawableShape(
			x::Abstract<sf::Shape> const& shapePtr,
			Element::TypeProperties const & properties);
	};
}
