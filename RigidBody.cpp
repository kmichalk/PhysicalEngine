#include "RigidBody.h"
#include "RigidRectangle.h"
#include "simple.h"
#include "PhysicalEngine.h"
#include "error.h"
#include "disp.h"

namespace phs
{
	//PhysicalEngine* RigidBody::parentEngine = nullptr;

	/*void RigidBody::setEngine(PhysicalEngine& enginePtr)
	{
		if (!parentEngine) parentEngine = &enginePtr;
		else throw x::error<>{RigidBody::SIM_SET,
			"Function setting static pointer to Simulation may only be called once."};
	}*/

	RigidBody::RigidBody(
		RigidBody const & other)
		:
		parentEngine	{other.parentEngine},
		parentObject	{other.parentObject},
		type			{other.type},
		collisionGroups_{DEFAULT_COLLISION_GROUP_},
		gravity			{other.gravity},
		static_			{other.static_},
		volume			{other.volume},
		dynamics		{other.dynamics},
		angularDynamics	{other.angularDynamics}
	{
	}

	phs::RigidBody::RigidBody(
		PhysicalEngine* engine,
		game::GameObject*	ownerPtr,
		ShapeType		type,
		basic_t			bound)
		:
		parentEngine	{engine},
		parentObject	{ownerPtr},
		type			{type},
		collisionGroups_{DEFAULT_COLLISION_GROUP_},
		gravity			{true},
		static_			{false},
		volume			{bound, 0.0, 0.0},
		dynamics		{Point::ZERO, Vector::ZERO, Vector::ZERO},
		angularDynamics	{0.0, 0.0, 0.0}
	{
	}

	phs::RigidBody::RigidBody(
		PhysicalEngine* engine,
		game::GameObject*	ownerPtr,
		ShapeType		type,
		basic_t			bound,
		Point const&	position,
		basic_t			angle)
		:
		parentEngine	{engine},
		parentObject	{ownerPtr},
		type			{type},
		collisionGroups_{DEFAULT_COLLISION_GROUP_},
		gravity			{true},
		static_			{false},
		volume			{bound, 0.0, 0.0},
		dynamics		{position, Vector::ZERO, Vector::ZERO},
		angularDynamics	{angle, 0.0, 0.0}

	{
	}

	void RigidBody::defaultState_()
	{
		if (gravity)
			dynamics.force = parentEngine->gravityAcc()*volume.mass;
		else
			dynamics.force.zero();
		angularDynamics.torque = 0;
	}

	void RigidBody::move(Vector const & vec)
	{
		dynamics.position += vec;
	}

	void RigidBody::move(basic_t time)
	{
		if (!static_) {
			linearMovement_(time);
			angularMovement_(time);
			//defaultState_();
		}
	}

	void RigidBody::linearMovement_(basic_t time)
	{
		Vector deltaVel = dynamics.force/volume.mass * time;
		dynamics.position += (dynamics.velocity+deltaVel/2.0)*time;
		dynamics.velocity += deltaVel;
	}

	void RigidBody::angularMovement_(basic_t time)
	{
		basic_t deltaAngVel = angularDynamics.torque/volume.inertiaMoment * time;
		angularDynamics.angle += (angularDynamics.angularVelocity+deltaAngVel/2.0)*time;
		angularDynamics.angularVelocity += deltaAngVel;
	}

	void RigidBody::directTowards_(Point const & target, basic_t velocityValue)
	{
		dynamics.velocity = (target - dynamics.position).setLen(velocityValue);
	}

	void RigidBody::rotateTowardsVelocity_()
	{
		angularDynamics.angle = dynamics.velocity.angle();
	}

	//void RigidBody::move()
	//{
	//	move(parentEngine->curFrame_);
	//}

	void RigidBody::stepBack()
	{
		dynamics.position -= dynamics.velocity*parentEngine->curFrame();
		angularDynamics.angle -= angularDynamics.angularVelocity*parentEngine->curFrame();
	}

	void RigidBody::stop()
	{
		dynamics.velocity.zero();
		dynamics.force.zero();
		angularDynamics.angularVelocity = 0;
		angularDynamics.torque = 0;
	}

	/*x::two<Point> RigidBody::AABB() const
	{
		return x::two<Point>();
	}*/

	void RigidBody::applyDefaults(Material::DefNum num)
	{
		apply(Material::defaults[num].physical);
	}

	void RigidBody::apply(PhysicalProp const & prop)
	{
		volume.mass = prop.density*surface();
		dynamics.force = parentEngine->gravityAcc()*volume.mass;
		volume.inertiaMoment = countInertiaMoment_();
		material = prop;
	}

	//void RigidBody::apply(Appearance const & appearance)
	//{
	//	/*shapeRef_.setFillColor(appearance.fillColor);
	//	shapeRef_.setOutlineColor(appearance.outlineColor);
	//	shapeRef_.setOutlineThickness(appearance.outline);*/
	//}

	void RigidBody::setStatic()
	{
		stop();
		volume.mass = std::numeric_limits<basic_t>::max();
		dynamics.force.zero();
		volume.inertiaMoment = std::numeric_limits<basic_t>::max();
		angularDynamics.torque = 0;
		gravity = false;
		static_ = true;
	}

	/*void RigidBody::setEngine(Engine* enginePtr)
	{
		if (!parentEngine) parentEngine = enginePtr;
		else throw x::error<phs::RigidBody>{0, "Attempt to change pointer to owner Engine."};
	}*/

	/*void RigidBody::refresh() const
	{
		setPosition(parentEngine->dispPos(dynamics.position));
		setRotation(-x::to_deg(angularDynamics.angle));
	}*/

	RigidBody::~RigidBody()
	{
		//kill();
	}

	/*std::ostream & operator<<(std::ostream & os, RigidBody const & obj)
	{
		return os << "pos: ", obj.dynamics.position, ", vel: ", obj.dynamics.velocity, endl,
			"ang: ", obj.angularDynamics.angle, ", angVel: ", obj.angularVel_, endl,
			"mass: ", obj.volume.mass, " inMom: ", obj.volume.inertiaMoment, endl,
			"bound: ", obj.volume.bound, " type: ", (obj.type == RigidBody::ShapeType::CIRCLE ? "Circle" : "Rectangle"), endl, endl;
	}*/

	RigidBody::Volume::Volume(
		basic_t bound, 
		basic_t mass, 
		basic_t inertiaMoment)
		:
		bound			{bound},
		mass			{mass},
		inertiaMoment	{inertiaMoment}
	{
	}

	void RigidBody::Volume::apply(RigidBody & object) const
	{
		object.volume = *this;
	}
	
	RigidBody::Dynamics::Dynamics(
		Point position, 
		Vector velocity, 
		Vector force)
		:
		position	{position},
		velocity	{velocity},
		force		{force}
	{
	}

	void RigidBody::Dynamics::apply(RigidBody & object) const
	{
		object.dynamics = *this;
	}

	RigidBody::AngularDynamics::AngularDynamics(
		basic_t angle, 
		basic_t angularVelocity,
		basic_t torque)
		:
		angle			{angle},
		angularVelocity	{angularVelocity},
		torque			{torque}
	{
	}

	void RigidBody::AngularDynamics::apply(RigidBody & object) const
	{
		object.angularDynamics = *this;
	}

	//x::va::pack<
	//	RigidBody::MemberPtr<volatile bool>,
	//	RigidBody::MemberPtr<volatile bool>,
	//	RigidBody::MemberPtr<volatile bool>,
	//	RigidBody::MemberPtr<volatile bool>,
	//	RigidBody::MemberPtr<basic_t>,
	//	RigidBody::MemberPtr<Point>,
	//	RigidBody::MemberPtr<Vector>,
	//	RigidBody::MemberPtr<Vector>,
	//	RigidBody::MemberPtr<basic_t>,
	//	RigidBody::MemberPtr<basic_t>,
	//	RigidBody::MemberPtr<basic_t>,
	//	RigidBody::MemberPtr<basic_t>,
	//	RigidBody::MemberPtr<basic_t>> const RigidBody::parameters_ 
	//	= 
	//	x::va::make_pack(
	//		&RigidBody::gravity,
	//		&RigidBody::static_,
	//		&RigidBody::stopped_,
	//		&RigidBody::onCollision_,
	//		&RigidBody::volume.bound,
	//		&RigidBody::dynamics.position,
	//		&RigidBody::dynamics.velocity,
	//		&RigidBody::dynamics.force,
	//		&RigidBody::angularDynamics.angle,
	//		&RigidBody::angularDynamics.angularVelocity,
	//		&RigidBody::angularDynamics.torque,
	//		&RigidBody::volume.mass,
	//		&RigidBody::volume.inertiaMoment);
}