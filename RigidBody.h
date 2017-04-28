#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <atomic>
#include "geom.h"
#include "simple.h"
#include "range.h"
#include "error.h"
#include "SFML\Graphics.hpp"
#include "Element.h"
#include "Material.h"
#include "bitmanager.h"


namespace game
{
	class GameObject;
}

namespace phs
{
	class Circle;
	class Rectangle;


	class RigidBody: virtual public Object
	{
		G_OBJECT;

		static constexpr auto DEFAULT_COLLISION_GROUP_ = x::bitmanager<16>::MemoryType{1};
	public:
		struct Volume
		{
			basic_t bound;
			basic_t mass;
			basic_t inertiaMoment;

			Volume(
				basic_t bound,
				basic_t mass,
				basic_t inertiaMoment);
			Volume(Volume const&) = default;
			Volume(Volume&&) = default;
			Volume& operator=(Volume const&) = default;

			void apply(RigidBody& object) const;
		};

		struct Dynamics
		{
			Point	position;
			Vector	velocity;
			Vector	force;

			Dynamics(
				Point position,
				Vector velocity,
				Vector force);
			Dynamics(Dynamics const&) = default;
			Dynamics(Dynamics&&) = default;
			Dynamics& operator=(Dynamics const&) = default;

			void apply(RigidBody& object) const;
		};

		struct AngularDynamics
		{
			basic_t angle;
			basic_t angularVelocity;
			basic_t torque;

			AngularDynamics(
				basic_t angle,
				basic_t angularVelocity,
				basic_t torque);
			AngularDynamics(AngularDynamics const&) = default;
			AngularDynamics(AngularDynamics&&) = default;
			AngularDynamics& operator=(AngularDynamics const&) = default;

			void apply(RigidBody& object) const;
		};

		friend class phs::DefaultCollisionSolver;
		friend class Volume;
		friend class Dynamics;
		friend class AngularDynamics;

		enum class ShapeType
		{
			CIRCLE = 0, RECTANGLE = 1
		};

		PhysicalEngine* const parentEngine;
		game::GameObject* const parentObject;
		ShapeType const type;
		x::bitmanager<16> collisionGroups_;

		volatile bool gravity;
		volatile bool static_;

	public:
		Volume			volume;
		Dynamics		dynamics;
		AngularDynamics angularDynamics;
		
		//static void setEngine(PhysicalEngine& enginePtr);

		RigidBody(RigidBody const& other);

		RigidBody(
			PhysicalEngine*		engine,
			game::GameObject*	ownerPtr, 
			ShapeType			type,
			basic_t				bound = 0.0);

		RigidBody(
			PhysicalEngine*		engine,
			game::GameObject*	ownerPtr,
			ShapeType		type, 
			basic_t			bound, 
			Point const&	position,
			basic_t			angle);

		virtual basic_t countInertiaMoment_() const abstract;
		void defaultState_();
		void linearMovement_(basic_t time);
		void angularMovement_(basic_t time);
		void directTowards_(Point const& target, basic_t velocityValue);
		void rotateTowardsVelocity_();

	public:
		
	/*	enum ParamNum
		{
			GRAVITY,
			STATIC,
			STOPPED,
			ON_COLLISION,
			BOUND,
			POSITION,
			VELOCITY,
			FORCE,
			ANGLE,
			ANGULAR_VELOCITY,
			TORQUE,
			MASS,
			INERTIA_MOMENT
		};*/

		enum ErrorType
		{
			WRONG_VALUE, SIM_SET, ABNORMAL_HIT
		};

		PhysicalProp material;
		
		void move(Vector const& vec);
		void move(basic_t time);
		//void move();
		void stepBack();
		void stop();
		
		virtual basic_t surface() const abstract;
		void applyDefaults(Material::DefNum num);
		virtual x::two<Point> AABB() const abstract;
		void setCollisionGroup(size_t groupNum, bool value);
		/*Volume const& volume() const;
		Dynamics const& dynamics() const;
		AngularDynamics const& angularDynamics() const;*/
		//void setEngine(Engine* enginePtr);

		/*Point getPosition() const;
		Vector getVelocity() const;*/
		/*basic_t getAngle() const;
		basic_t getAngularVelocity() const;
		basic_t getMass() const;
		basic_t getInertiaMoment() const;*/

		//void setPosition(Point const& posiition);
		//void setVelocity(Vector const& velocity);
		//void setAngle(basic_t angle);
		//void setAngularVelocity(basic_t angularVel);
		//void setMass(basic_t mass);
		//void setInertiaMoment(basic_t inertiaMoment);


		void apply(PhysicalProp const& prop);		
		void setStatic();

		friend std::ostream& operator<<(std::ostream& os, RigidBody const& obj);

		virtual ~RigidBody();
	};

#pragma region OBJECT_GETTERS

	inline void RigidBody::setCollisionGroup(size_t groupNum, bool value)
	{
		collisionGroups_.setBit(groupNum, value);
	}

	//inline RigidBody::Volume const& RigidBody::volume() const
	//{
	//	return volume;
	//}

	//inline RigidBody::Dynamics const& RigidBody::dynamics() const
	//{
	//	return dynamics;
	//}

	//inline RigidBody::AngularDynamics const& RigidBody::angularDynamics() const
	//{
	//	return angularDynamics;
	//}

	/*inline Point RigidBody::getPosition() const
	{
		return dynamics.position;
	}
	inline Vector RigidBody::getVelocity() const
	{
		return dynamics.velocity;
	}
	inline basic_t RigidBody::getAngle() const
	{
		return angularDynamics.angle;
	}
	inline basic_t RigidBody::getAngularVelocity() const
	{
		return angularDynamics.angularVelocity;
	}
	inline basic_t RigidBody::getMass() const
	{
		return volume.mass;
	}
	inline basic_t RigidBody::getInertiaMoment() const
	{
		return volume.inertiaMoment;
	}*/
#pragma endregion

#pragma region OBJECT_SETTERS

	/*inline void RigidBody::setPosition(Point const& position)
	{
		dynamics.position = position;
	}

	inline void RigidBody::setVelocity(Vector const& velocity)
	{
		dynamics.velocity = velocity;
	}

	inline void RigidBody::setAngle(basic_t angle)
	{
		angularDynamics.angle = angle;
	}

	inline void RigidBody::setAngularVelocity(basic_t angularVel)
	{
		angularDynamics.angularVelocity = angularVel;
	}

	inline void RigidBody::setMass(basic_t mass)
	{
		volume.mass = mass;
	}

	inline void RigidBody::setInertiaMoment(basic_t inertiaMoment)
	{
		volume.inertiaMoment = inertiaMoment;
	}*/

#pragma endregion
}

#endif //PHYSICAL_OBJECT_H
