#include "RigidRectangle.h"
#include "PhysicalEngine.h"
#include "crd_cast.h"
#include "autolim.h"

namespace phs
{
	void Rectangle::findVertices_(Point vertArr[4]) const
	{		
		Vector A = Vector::versor(angularDynamics.angle)*(size_.x/2.0);
		Vector B = Vector::versor(angularDynamics.angle+PI/2.0)*(size_.y/2.0);
		/*autoinit(vertArr, 
			dynamics.position+A+B,
			dynamics.position+A-B,
			dynamics.position-A-B,
			dynamics.position-A+B);*/
		 
		vertArr[0] = dynamics.position+A+B;
		vertArr[1] = dynamics.position+A-B;
		vertArr[2] = dynamics.position-A-B;
		vertArr[3] = dynamics.position-A+B;
	}

	//const Point* Rectangle::findVertices_() const
	//{
	//	//if (!vertActual_) {
	//		//vertices_.clear();
	//		Vector A = Vector::versor(angularDynamics.angle)*(size_.x/2.0);
	//		Vector B = Vector::versor(angularDynamics.angle+PI/2.0)*(size_.y/2.0);
	//		vertices_[0] = dynamics.position+A+B;
	//		vertices_[1] = dynamics.position+A-B;
	//		vertices_[2] = dynamics.position-A-B;
	//		vertices_[3] = dynamics.position-A+B;
	//	//}
	//	return vertices_;
	//	//if (!vertices_) {
	//	////vertices_.clear();
	//	//	Vector A = Vector::versor(angularDynamics.angle)*(size_.x/2.0);
	//	//	Vector B = Vector::versor(angularDynamics.angle+PI/2.0)*(size_.y/2.0);
	//	//	vertices_.append({dynamics.position+A+B, dynamics.position+A-B, dynamics.position-A-B, dynamics.position-A+B});
	//	//}
	//	//return vertices_.content();
	//}

	//void Rectangle::clearVertices_()
	//{
	//	vertActual_ = false;
	//	//vertices_.clear();
	//}

	//void Rectangle::draw(sf::RenderTarget & target, sf::RenderStates states) const
	//{
	//	if (visible_) {
	//		refresh();
	//		target.draw(shape_, states);
	//	}
	//}

	basic_t Rectangle::surface() const
	{
		return size_.x*size_.y;
	}

	basic_t Rectangle::countInertiaMoment_() const
	{
		return volume.mass*(x::pow2(size_.x) + x::pow2(size_.y)) / 12.0;
	}

	/*void Rectangle::setColor(sf::Color color)
	{
		shape_.setFillColor(color);
	}*/

	x::two<Point> Rectangle::AABB() const
	{
		x::Min<basic_t> minX, minY;
		x::Max<basic_t> maxX, maxY;
		Point vertArr[4];
		findVertices_(vertArr);
		for (auto&& v : vertArr) {
			minX(v.x); maxX(v.x);
			minY(v.y); maxY(v.y);
		}
		return{{minX(),minY()},{maxX(),maxY()}};
	}

	phs::Rectangle::Rectangle(
		PhysicalEngine* engine,
		game::GameObject* ownerPtr):
		RigidBody{engine, ownerPtr, ShapeType::RECTANGLE}
		//vertActual_{false}
		//vertices_{4}
	{
	}

	Rectangle::Rectangle(Rectangle const & other):
		RigidBody	(other),
		size_		{other.size_}
	{
	}

	Rectangle::Rectangle(
		PhysicalEngine* engine,
		game::GameObject* ownerPtr, 
		Size const & size, 
		Point const & position, 
		basic_t angle)
		:
		RigidBody	{engine,ownerPtr, ShapeType::RECTANGLE, hypot(size)/2.0, position, angle},
		size_		{size}
	{
	}

}