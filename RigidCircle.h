#ifndef PHYSICAL_CIRCLE_H
#define PHYSICAL_CIRCLE_H

#include "RigidBody.h"
namespace phs
{
	class Circle: public RigidBody
	{
		G_OBJECT;
		//void setShapePosition_();
		//void actualizeShapeGeom_();
	public:
		friend class phs::DefaultCollisionSolver;

		/*sf::CircleShape shape_;*/


		//bool edgeCollision(Point const& A, Point const& B, Point& colPos, Vector& colDir) const;
		//void virtual draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
		/*void virtual move(Vector const& vec) override;
		void virtual move(basic_t time) override;*/
		virtual basic_t surface() const override;
		virtual basic_t countInertiaMoment_() const override;
		//void virtual setColor(sf::Color color) override;
		virtual x::two<Point> AABB() const override;

	public:
		Circle(PhysicalEngine* engine, game::GameObject* ownerPtr);

		Circle(
			Circle const& other);

		Circle(
			PhysicalEngine* engine,
			game::GameObject* ownerPtr,
			basic_t radius, 
			Point const& position = Point::ZERO, 
			basic_t angle = 0);
	};
}
#endif
