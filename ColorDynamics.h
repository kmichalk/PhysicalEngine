#pragma once

#include "SFML\Graphics\Color.hpp"
#include "TimePeriod.h"


namespace game
{
	class DrawableShape;

	class ColorDynamics
	{
		DrawableShape* target_;

	public:
		void attach(DrawableShape* target)
		{
			target_ = target;
		}

		virtual void process() abstract;
	};
}