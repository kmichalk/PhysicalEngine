#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include "Element.h"
#include "locatable.h"
#include "MemberAbstract.h"

namespace game
{
	class GameObject;	

	/*class PositionAbstract
	{
	public:
		void virtual apply(GameObject& object) const abstract;
		Point virtual get() const abstract;
	};

	class ConstPosition:
		public PositionAbstract
	{
		Point dynamics.position;
	public:
		ConstPosition(Point const& position);
		void virtual apply(GameObject& object) const override;
		Point virtual get() const override;
	};

	class ObjectPosition:
		public PositionAbstract
	{
		Locatable const* trackedObject_;
	public:
		ObjectPosition(ObjectPosition const& other);
		ObjectPosition(Locatable const* trackedObject);
		void virtual apply(GameObject& object) const override;
		Point virtual get() const override;
	};

	class VelocityAbstract
	{
	public:
		void virtual apply(GameObject& object) const abstract;
		Point virtual get() const abstract;
	};

	class ConstVelocity:
		public VelocityAbstract
	{
		Vector dynamics.velocity;
	public:
		ConstVelocity(Vector const& velocity);
		void virtual apply(GameObject& object) const override;
		Point virtual get() const override;
	};

	class ObjectVelocity:
		public VelocityAbstract
	{
		GameObject const* trackedObject_;
	public:
		ObjectVelocity(GameObject const* trackedObject);
		void virtual apply(GameObject& object) const override;
		Point virtual get() const override;
	};

	class VelocityTowards:
		public VelocityAbstract
	{
		x::Abstract<PositionAbstract> dynamics.position;
		basic_t value_;
	public:
		VelocityTowards(x::Abstract<PositionAbstract> const& position, basic_t value);
		void virtual apply(GameObject& object) const override;
		Point virtual get() const override;
	};

	class AngleAbstract
	{
	public:
		void virtual apply(GameObject& object) const abstract;
		virtual basic_t get() const abstract;
	};

	class ConstAngle:
		public AngleAbstract
	{
		basic_t angularDynamics.angle;
	public:
		ConstAngle(basic_t angle);
		void virtual apply(GameObject& object) const override;
		virtual basic_t get() const override;
	};

	class ObjectAngle:
		public AngleAbstract
	{
		GameObject const* trackedObject_;
	public:
		ObjectAngle(GameObject const* trackedObject);
		void virtual apply(GameObject& object) const override;
		virtual basic_t get() const override;
	};

	class AngleTowards:
		public AngleAbstract
	{
		x::Abstract<PositionAbstract> dynamics.position;
	public:
		AngleTowards(AngleTowards const& other);
		AngleTowards(x::Abstract<PositionAbstract> const& position);
		void virtual apply(GameObject& object) const override;
		virtual basic_t get() const override;
	};*/


	/*using Position = Member<Point, phs::RigidBody, &phs::RigidBody::dynamics.position>;
	using Velocity = Member<Vector, phs::RigidBody, &phs::RigidBody::dynamics.velocity>;
	using Force = Member<Vector, phs::RigidBody, &phs::RigidBody::dynamics.force>;
	using Angle = Member<basic_t, phs::RigidBody, &phs::RigidBody::angularDynamics.angle>;
	using AngularVelocity = Member<Vector, phs::RigidBody, &phs::RigidBody::dynamics.velocity>;*/

	class DynamicsApplier
	{
	protected:
		static ValueAbstract<Vector> DEFAULT_VELOCITY_;
		static ValueAbstract<Vector> DEFAULT_FORCE_;

		ValueAbstract<Point>  position_;
		ValueAbstract<Vector> velocity_;
		ValueAbstract<Vector> force_;

	public:
		DynamicsApplier(
			DynamicsApplier const& other) = default;

		DynamicsApplier(
			ValueAbstract<Point>  const& position,
			ValueAbstract<Vector> const& velocity	= DEFAULT_VELOCITY_,
			ValueAbstract<Vector> const& force		= DEFAULT_FORCE_);

		void virtual apply(phs::RigidBody& object) const;
	};



	class Shooter:
		public DynamicsApplier
	{
	protected:
		ValueAbstract<Point>	target_;
		ValueAbstract<basic_t>	initialVelocity_;

	public:
		Shooter(
			Shooter const&) = default;

		Shooter(
			ValueAbstract<Point>	const& position,
			ValueAbstract<Point>	const& target,
			ValueAbstract<basic_t>	const& initialVelocity,
			ValueAbstract<Vector>	const& force			= DEFAULT_FORCE_);

		void virtual apply(phs::RigidBody& object) const override;
	};



	class AngularDynamicsApplier
	{
		ValueAbstract<basic_t> angle_;
		ValueAbstract<basic_t> angularVelocity_;
		ValueAbstract<basic_t> torque_;

	public:
		AngularDynamicsApplier(
			AngularDynamicsApplier const& other) = default;

		AngularDynamicsApplier(
			ValueAbstract<basic_t> const& angle,
			ValueAbstract<basic_t> const& angularVelocity,
			ValueAbstract<basic_t> const& torque);

		void apply(phs::RigidBody& object) const;
	};


	class ObjectFactory
	{
	public:
		UseManager nUsers;

		ObjectFactory();

		GameObject* createRectangle(Size size, Point position, basic_t angle = 0) const;
	};
}

#endif //OBJECT_FACTORY_H
