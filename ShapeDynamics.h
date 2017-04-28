#pragma once

#include "ColorDynamics.h"
#include "TimePeriod.h"

namespace sf
{
	class Shape;
}

namespace game
{
	class DrawableShape;

	class ShapeDynamics
	{
		TimePeriod period_;

		void applySizeChange_(sf::Shape* target);
		void applyAngleChange_(sf::Shape* target);

	public:
		float sizeChangeX;
		float sizeChangeY;
		float sizeChangeAccX;
		float sizeChangeAccY;

		float angleChange;
		float angleChangeAcc;

		ColorDynamics* colorChange;

		ShapeDynamics(
			double period,
			float sizeChangeX,
			float sizeChangeY,
			float sizeChangeAccX,
			float sizeChangeAccY,
			float angleChange,
			float angleChangeAcc,
			ColorDynamics* colorChange = nullptr);

		void apply(sf::Shape* target);
	};
}