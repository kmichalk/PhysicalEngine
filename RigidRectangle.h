#ifndef PHYSICAL_RECTANGLE_H
#define PHYSICAL_RECTANGLE_H

#include "RigidBody.h"
#include "xvector.h"

namespace phs
{

	class Rectangle: public RigidBody/*, enumed*/
	{
		G_OBJECT;
	public:
		//mutable x::vector<Point> vertices_;
		//mutable Point vertices_[4];
		//mutable bool vertActual_;
		Size size_;

		//sf::RectangleShape shape_;

		void findVertices_(Point vertArr[4]) const;
		//const Point* findVertices_() const;
		//void clearVertices_();
		//void virtual draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
		virtual basic_t surface() const override;
		virtual basic_t countInertiaMoment_() const override;
		//void virtual setColor(sf::Color color) override;
		virtual x::two<Point> AABB() const override;

	public:
		friend class phs::DefaultCollisionSolver;

		Rectangle(
			PhysicalEngine* engine,
			game::GameObject* ownerPtr);

		Rectangle(
			Rectangle const& other);

		Rectangle(
			PhysicalEngine* engine,
			game::GameObject* ownerPtr,
			Size const& size,
			Point const& position = Point::ZERO,
			basic_t angle = 0);
	};
}

#endif