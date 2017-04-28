#include "RigidCircle.h"
#include "PhysicalEngine.h"
#include "crd_cast.h"

namespace phs
{
	/*void Circle::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (visible_) {
			refresh();
			target.draw(*this, states);
		}
	}*/

	basic_t Circle::surface() const
	{
		return PI*x::pow2(volume.bound);
	}

	basic_t Circle::countInertiaMoment_() const
	{
		return volume.mass*x::pow2(volume.bound)/2.0;
	}

	/*void Circle::setColor(sf::Color color)
	{
		shape_.setFillColor(color);
	}*/

	x::two<Point> Circle::AABB() const
	{
		return
		{{dynamics.position.x-volume.bound,dynamics.position.y-volume.bound},
		{dynamics.position.x+volume.bound,dynamics.position.y+volume.bound}};
	}

	phs::Circle::Circle(PhysicalEngine* engine, game::GameObject* ownerPtr):
		RigidBody{engine, ownerPtr,ShapeType::CIRCLE}
	{
	}

	Circle::Circle(Circle const & other)
		:
		RigidBody(other)
	{
	}

	Circle::Circle(
		PhysicalEngine* engine,
		game::GameObject* ownerPtr, 
		basic_t radius, 
		Point const & position, 
		basic_t angle)
		:
		RigidBody{engine, ownerPtr, ShapeType::CIRCLE, radius, position, angle}
	{
	}
}