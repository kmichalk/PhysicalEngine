#include "ShapeDynamics.h"
#include "SFML\Graphics\Shape.hpp"


namespace game
{
	void ShapeDynamics::applySizeChange_(sf::Shape * target)
	{
		target->setScale({
			1.0f + float(sizeChangeX * period_.percentage()),
			1.0f + float(sizeChangeY* period_.percentage())});
	}

	void ShapeDynamics::applyAngleChange_(sf::Shape * target)
	{
		target->setRotation(angleChange);
	}

	ShapeDynamics::ShapeDynamics(
		double period,
		float sizeChangeX,
		float sizeChangeY,
		float sizeChangeAccX,
		float sizeChangeAccY,
		float angleChange,
		float angleChangeAcc,
		ColorDynamics * colorChange)
		:
		period_{period},
		sizeChangeX{sizeChangeX},
		sizeChangeY{sizeChangeY},
		sizeChangeAccX{sizeChangeAccX},
		sizeChangeAccY{sizeChangeAccY},
		angleChange{angleChange},
		angleChangeAcc{angleChangeAcc},
		colorChange{colorChange}
	{
	}

	void ShapeDynamics::apply(sf::Shape * target)
	{

	}
}