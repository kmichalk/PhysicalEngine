#include "GameObject.h"
#include "PhysicalEngine.h"

#include "crd_cast.h"

namespace game
{
	//CircleObject::CircleObject()
	//	:
	//	GameObject{{},
	//		{}}
	//{
	//}

	CircleObject::CircleObject(
		basic_t			radius, 
		Point const&	position,
		basic_t			angle)
		:
		GameObject{
			x::New<sf::CircleShape>{(float)(radius*enginePtr_->absScale())},
			x::New<phs::Circle>{enginePtr_, this, radius, position, angle}}
	{
		//shape_->setOrigin((float)radius*parentEngine->absScale(), (float)radius*parentEngine->absScale());
	}

	//RectangleObject::RectangleObject()
	//	:
	//	GameObject{x::New<sf::RectangleShape>{},
	//		x::New<phs::Rectangle>{}}
	//{
	//}

	RectangleObject::RectangleObject(
		Size const&		size, 
		Point const&	position,
		basic_t			angle)
		:
		GameObject{
			x::New<sf::RectangleShape>{crd_cast<sf::Vector2f>(size*enginePtr_->absScale())}, 
			x::New<phs::Rectangle>{enginePtr_, this, size, position, angle}}
	{
		//shape_->setOrigin(((sf::RectangleShape*)shape_)->getSize()/2.0f);
	}

	

	/*GameObject::GameObject(sf::Shape & shapeRef, phs::RigidBody& phsObjRef):
		shapeRef_{shapeRef},
		phsObjRef_{phsObjRef}
	{
	}*/

	/*RigidBody::RigidBody(sf::Shape & shapeRef, phs::RigidBody& phsObjRef, Point const & position, basic_t angle):
		shapeRef_{shapeRef},
		phsObjRef_{phsObjRef}
	{
	}*/
	GameObject::GameObject(GameObject const& other)
		:
		DrawableShape	{other},
		physicalObject_	{other.physicalObject_}
	{
		centerOrigin_();
	}


	GameObject::GameObject(
		x::Abstract<sf::Shape> const&	shapePtr,
		x::Abstract<phs::RigidBody> const& phsObjPtr,
		Element::TypeProperties const&	properties)
		:
		DrawableShape		{shapePtr, properties},
		physicalObject_		{phsObjPtr}
	{
		centerOrigin_();
	}

	void GameObject::applyDefaults(Material::DefNum num)
	{
		physicalObject_->apply(Material::defaults[num].physical);
		DrawableShape::apply(Material::defaults[num].appearance);
	}

	void GameObject::refresh()
	{
		shape_->setPosition(enginePtr_->dispPos(physicalObject_->dynamics.position));
		shape_->setRotation(-x::to_deg(physicalObject_->angularDynamics.angle));
	}

	//void GameObject::setPosition(Point const& position)
	//{
	//	//DrawableShape::setPosition(position);
	//	physicalObject_->setPosition(position);
	//}

	Point GameObject::getPosition() const
	{
		return physicalObject_->dynamics.position;
	}

	//void GameObject::setVelocity(Vector const& velocity)
	//{
	//	physicalObject_->setVelocity(velocity);
	//}

	//Vector GameObject::getVelocity() const
	//{
	//	return physicalObject_->getVelocity();
	//}

	//void GameObject::setAngle(basic_t angle)
	//{
	//	physicalObject_->setAngle(angle);
	//}

	//basic_t GameObject::getAngle() const
	//{
	//	return physicalObject_->getAngle();
	//}
}

phs::PhysicalEngine* game::Element::enginePtr_ = nullptr;