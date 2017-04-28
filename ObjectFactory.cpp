#include "ObjectFactory.h"
#include "RigidRectangle.h"
#include "RigidCircle.h"
#include "GameObject.h"

namespace game
{
	ObjectFactory::ObjectFactory()
	{
	}

	GameObject * ObjectFactory::createRectangle(Size size, Point position, basic_t angle) const
	{
		return nullptr;
	}

	//DynamicsApplier::DynamicsApplier(
	//	DynamicsApplier const & other)
	//	:
	//	dynamics.position	{other.dynamics.position},
	//	dynamics.velocity	{other.dynamics.velocity},
	//	dynamics.force		{other.dynamics.force}
	//{
	//}

	DynamicsApplier::DynamicsApplier(
		ValueAbstract<Point>	const & position, 
		ValueAbstract<Vector>	const & velocity, 
		ValueAbstract<Vector>	const & force)
		:
		position_	{position},
		velocity_	{velocity},
		force_		{force}
	{
	}

	void DynamicsApplier::apply(phs::RigidBody & object) const
	{
		object.dynamics.position	= position_->get();
		object.dynamics.velocity	= velocity_->get();
		object.dynamics.force		= force_->get();
	}

	//AngularDynamicsApplier::AngularDynamicsApplier(
	//	AngularDynamicsApplier const & other)
	//	:
	//	angularDynamics.angle			{other.angularDynamics.angle},
	//	angularDynamics.angularVelocity{other.angularDynamics.angularVelocity},
	//	angularDynamics.torque			{other.angularDynamics.torque}
	//{
	//}

	AngularDynamicsApplier::AngularDynamicsApplier(
		ValueAbstract<basic_t>	const & angle, 
		ValueAbstract<basic_t>	const & angularVelocity, 
		ValueAbstract<basic_t>	const & torque)
		:
		angle_			{angle},
		angularVelocity_{angularVelocity},
		torque_			{torque}
	{
	}

	void AngularDynamicsApplier::apply(phs::RigidBody & object) const
	{
		object.angularDynamics.angle			= angle_->get();
		object.angularDynamics.angularVelocity = angularVelocity_->get();
		object.angularDynamics.torque			= torque_->get();
	}

	Shooter::Shooter(
		ValueAbstract<Point>	const & position, 
		ValueAbstract<Point>	const & target,
		ValueAbstract<basic_t>	const & initialVelocity,
		ValueAbstract<Vector>	const & force)
		:
		DynamicsApplier	(position, DEFAULT_VELOCITY_, force),
		target_			{target},
		initialVelocity_{initialVelocity}
	{
	}

	void Shooter::apply(phs::RigidBody & object) const
	{
		object.dynamics.position = position_->get();
		object.dynamics.force	 = force_->get();
		object.directTowards_(target_->get(), initialVelocity_->get());
		object.rotateTowardsVelocity_();
	}

	ValueAbstract<Vector> DynamicsApplier::DEFAULT_VELOCITY_	= Value<Vector>::createConst({0,0});
	ValueAbstract<Vector> DynamicsApplier::DEFAULT_FORCE_		= Value<Vector>::createConst({0,0});
}