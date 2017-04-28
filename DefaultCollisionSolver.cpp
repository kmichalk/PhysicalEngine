#include "DefaultCollisionSolver.h"
#include "autolim.h"
#include "PhysicalEngine.h"
#include "disp.h"
#include "xrnd.h"

#pragma region COLLIDER_MACROS
#define bound_1 object1_->volume.bound
#define bound_2 object2_->volume.bound
#define _r obj->bound_
#define mass_1 object1_->volume.mass
#define mass_2 object2_->volume.mass
#define _m obj->mass_
#define position_1 object1_->dynamics.position
#define position_2 object2_->dynamics.position
#define _P obj->position_
#define velocity_1 object1_->dynamics.velocity
#define velocity_2 object2_->dynamics.velocity
#define _v obj->velocity_
#define angularVelocity_1 object1_->angularDynamics.angularVelocity
#define angularVelocity_2 object2_->angularDynamics.angularVelocity
#define _av obj->angularVelocity_
#define angle_1 object1_->angularDynamics.angle
#define angle_2 object2_->angularDynamics.angle
#define _an obj->angle_
#define inertiaMoment_1 object1_->volume.inertiaMoment
#define inertiaMoment_2 object2_->volume.inertiaMoment
#define _I obj->inertiaMoment_
#define COR_1 object1_->material.restitution
#define COR_2 object2_->material.restitution
#define _COR obj->material.restitution
#define force_1 object1_->dynamics.force
#define force_2 object2_->dynamics.force
#define torque_1 object1_->angularDynamics.torque
#define torque_2 object2_->angularDynamics.torque

#define _isCir(_ptr) _ptr->type == phs::RigidBody::ShapeType::CIRCLE
#define _isRect(_ptr) _ptr->type == phs::RigidBody::ShapeType::RECTANGLE
#pragma endregion

using namespace std;
namespace phs
{
	basic_t DefaultCollisionSolver::minColDirLength = DEFAULT_MIN_COL_DIR_LENGTH;

	DefaultCollisionSolver::DefaultCollisionSolver():
		swapSeparate_{false},
		object1_{nullptr},
		object2_{nullptr},
		colPos_{},
		colDir_{}
	{
	}

	DefaultCollisionSolver::DefaultCollisionSolver(DefaultCollisionSolver const &):
		DefaultCollisionSolver()
	{
	}

	DefaultCollisionSolver::DefaultCollisionSolver(RigidBody * obj1, RigidBody * obj2):
		object1_{obj1}, object2_{obj2}, swapSeparate_{false}
	{
	}

	bool DefaultCollisionSolver::RectContainsPoint_(const Point vertArr[4], Point const& center, Point const & P)
	{
		int relArr[4];
		int iMin;
		basic_t dist2i;
		basic_t dist2Min = std::numeric_limits<basic_t>::max();

		iter(i, 0, 3) {
			line<basic_t> edge{vertArr[i], vertArr[(i+1)%4]};
			relArr[i] = x::sgn(edge.relation(P));
			if (x::sgn(edge.relation(center))!=relArr[i] && 
				(dist2i = edge.dist2(P)) < dist2Min) {
				dist2Min = dist2i;
				iMin = i;
			}
		}

		if (relationsDenoteInclusion_(relArr) && iMin>=0) {
			colPos_ = P;
			colDir_ = (vertArr[(iMin+1)%4]-vertArr[iMin]);
			colDir_.rot90p().setLen(sqrt(dist2Min)+minColDirLength);
			return true;
		}
		return false;
	}

	bool DefaultCollisionSolver::matchingCollisionFunc_()
	{
		return (this->*colFuncs_[(int)object1_->type][(int)object2_->type])(object1_, object2_);
	}

	/*bool CollisionSolver::RectContainsPoint_(const Point vertArr[4], Point const & P)
	{
		int in1 = 0, in2 = 0;
		int iMin;
		basic_t dist2Min = std::numeric_limits<basic_t>::max();
		for (int i = 0; i<4; ++i) {
			line<basic_t> edge{vertArr[i], vertArr[(i+1)%4]};

			basic_t d{edge.dist2(P)};
			if (d < dist2Min) {
				dist2Min = d;
				iMin = i;
			}
			if (edge.relation(P) < 0) {
				if (in2) return false;
				(in1 ? in2 : in1) = i+1;
			}
		}
		
		if ((in2-in1)==1 || (in2==4 && in1==1)) {
			colPos_ = P;
			colDir_ = (vertArr[(iMin+1)%4]-vertArr[iMin]).rot90p().setLen(sqrt(dist2Min)+minColDirLength);
			return true;
		}
		return false;
	}*/

	bool DefaultCollisionSolver::CirCrossEdge_(Circle * cir, Point const & A, Point const & B)
	{
		static const x::range<double> r01{0,1};
		Vector edge{B-A};
		colDir_ = edge.normal().setLen(cir->volume.bound);
		colPos_ = cir->dynamics.position + colDir_;
		Vector rVec{colPos_-cir->dynamics.position};
		basic_t crossParam{crossVal(rVec, edge)};
		if (crossParam==0) return false;
		Vector computeParam{(A-cir->dynamics.position)/crossParam};
		basic_t t{crossVal(computeParam, edge)};
		basic_t u{crossVal(computeParam, rVec)};
		if (r01.contains(t) && r01.contains(u)) {
			colDir_.setLen(cir->volume.bound*(1.0-t)+minColDirLength);
			return true;
		}
		return false;
	}

	bool DefaultCollisionSolver::CirContainsPoint_(Circle * cir, Point const & P)
	{
		colDir_ = P-cir->dynamics.position;
		basic_t dirLen2 = colDir_.len2();
		if (dirLen2 < x::pow2(cir->volume.bound)) {
			colPos_ = P;
			colDir_.setLen(cir->volume.bound - sqrt(dirLen2) + minColDirLength);
			return true;
		}
		return false;
	}

	/*bool CollisionSolver::CirCrossEdge_(Circle * obj, Point const & A, Point const & B)
	{
		static const x::range<double> r01{0.0,1.0};
		Vector edge = B-A;
		Vector PA = A-_P;

		auto solution{
			x::solve_eq(
				edge.len2(),
				(PA*edge)*2,
				PA.len2()-x::pow2(_r))};

		if (x::is_nan(solution.a)) return false;

		if (r01.contains(solution.a)) {
			if (r01.contains(solution.b))
				colPos_ = A+(edge*((solution.a+solution.b)/2.0));
			else
				colPos_ = A+(edge*solution.a);
		}
		else if (r01.contains(solution.b))
			colPos_ = A+(edge*solution.b);
		else return false;

		colDir_ = colPos_-_P;
		colDir_.setLen(abs(_r-colDir_.len()) + minColDirLength);
		return true;
	}*/

	bool DefaultCollisionSolver::bothStatic_() const
	{
		return object1_->static_ && object2_->static_;
	}

	bool DefaultCollisionSolver::bothStopped_() const
	{
		return velocity_1.len2() < 0.01 && velocity_2.len2() < 0.01;
	}

	bool DefaultCollisionSolver::bothValid_() const
	{
		return object1_!=object2_ && object1_ && object2_;
	}

	bool DefaultCollisionSolver::relationsDenoteInclusion_(int relArr[4]) const
	{
		return relArr[0]!=relArr[2] && relArr[1]!=relArr[3];
	}

	bool DefaultCollisionSolver::collisionGroupsOverlap_() const
	{
		return bool(object1_->collisionGroups_ & object2_->collisionGroups_);
	}

	basic_t DefaultCollisionSolver::responseCoefficient_(
		Vector const& colVersor, 
		Vector const& colR1, 
		Vector const& colR2)
	{
		return 
			(colVersor
			*(
				velocity_1 -
				colR1.crossVal(angularVelocity_1) -
				velocity_2 +
				colR2.crossVal(angularVelocity_2)
				)
			)
			/(
				1.0/mass_1 +
				1.0/mass_2 +
				(x::pow2(colR1.crossVal(colVersor))/inertiaMoment_1) +
				(x::pow2(colR2.crossVal(colVersor))/inertiaMoment_2)
				);
	}

	bool DefaultCollisionSolver::boundsCollide_()
	{
		return x::pow2(bound_1+bound_2) > (position_2-position_1).len2();
	}

	void DefaultCollisionSolver::process(phs::RigidBody* o1, phs::RigidBody* o2)
	{
		setObjects_(o1, o2);

		swapSeparate_ = false;
		if (bothValid_()){
			//++obj1_->nUsers;
			//++obj2_->nUsers;			
			if (boundsCollide_() && 
				collisionGroupsOverlap_() && 
				!bothStatic_()) 
			{
				if ( ! matchingCollisionFunc_()) {
					o1->defaultState_();
					o2->defaultState_();
				}
			}
			//--obj1_->nUsers;
			//--obj2_->nUsers;
		}
		//else {
		//	throw x::error<CollisionSolver>{}; //TODO: CollisionSolver errors
		//}
	}

	void DefaultCollisionSolver::setObjects_(RigidBody * obj1, RigidBody * obj2)
	{
		object1_ = obj1;
		object2_ = obj2;
	}

	void DefaultCollisionSolver::separate_()
	{
		double swapParam = swapSeparate_ ? -1 : 1;
		basic_t sumMass = (mass_1+mass_2);
		object1_->move(-colDir_*(swapParam*mass_2/sumMass));
		object2_->move(colDir_*(swapParam*mass_1/sumMass));
	}

	void DefaultCollisionSolver::solveStaticCollision_()
	{
		//Vector colVersor{colDir_.dir()};
		double staticParam = swapSeparate_ ? -1 : 1;
		basic_t sumMass = (mass_1+mass_2);
		/*_F1 -= colVersor*((0.0001*staticParam*_r1/RigidBody::parentEngine->curFrame())*(_m2/sumMass));
		_F2 += colVersor*((0.0001*staticParam*_r2/RigidBody::parentEngine->curFrame())*(_m1/sumMass));*/
		force_1 -= colDir_*(staticParam*(mass_2/sumMass));
		force_2 += colDir_*(staticParam*(mass_1/sumMass));
		//obj1_->move(-colDir_*(staticParam*_m2/sumMass));
		//obj2_->move(colDir_*(staticParam*_m1/sumMass));
	}

	void DefaultCollisionSolver::solveDynamicCollision_()
	{
		force_1 = object1_->parentEngine->gravityAcc()*mass_1;
		force_2 = object2_->parentEngine->gravityAcc()*mass_2;
	}

	void DefaultCollisionSolver::calcFriction_()
	{
		if (!object1_->static_) {
			Vector velProj1{-project(velocity_1,colDir_.normal()).dir()};
			Vector fric1{velProj1*(project(force_1, colDir_).len())*object1_->material.friction};
			torque_1 += project(fric1, velProj1).len()*(colPos_-position_1).len();
			force_1 += fric1;
		}
		if (!object2_->static_) {
			Vector velProj2{-project(velocity_2,colDir_.normal()).dir()};
			Vector fric2{velProj2*(project(force_2, colDir_).len())*object2_->material.friction};
			torque_2 += project(fric2, velProj2).len()*(colPos_-position_2).len();
			force_2 += fric2;
		}
	}

	void DefaultCollisionSolver::solveCollision_()
	{
		
		//solveStaticCollision_();
		//calcFriction_();
		separate_();
		colDir_ = colDir_.dir();
		if (bothStopped_()) {		
			solveStaticCollision_();
			return;
		}		

		Vector colVersor{colDir_};
		Vector colR1 = colPos_-position_1;
		Vector colR2 = colPos_-position_2;

		basic_t j = responseCoefficient_(colVersor, colR1, colR2);

		if (!object1_->static_) {
			velocity_1 -= colVersor*((1.0+COR_1)*j/mass_1);
			angularVelocity_1 += (colVersor*(j*(1.0+COR_1))).crossVal(colR1)/inertiaMoment_1;
		}
		if (!object2_->static_) {
			velocity_2 += colVersor*((1.0+COR_2)*j/mass_2);
			angularVelocity_2 -= (colVersor*(j*(1.0+COR_2))).crossVal(colR2)/inertiaMoment_2;
		}
	}

	bool DefaultCollisionSolver::calcCollision_(Circle * object1_, Circle * object2_)
	{
		colDir_ = position_2-position_1;
		colDir_.setLen(bound_1+bound_2-colDir_.len() + minColDirLength);
		colPos_ = position_1 + (colDir_*(bound_1 / (bound_1+bound_2)));
		solveCollision_();
		return true;
	}

	bool DefaultCollisionSolver::calcCollision_(Circle * cir, Rectangle * rect)
	{
		Point vertArr[4];
		rect->findVertices_(vertArr);
		//const Point* vertArr = rect->findVertices_();
		iter(i, 0, 3) {
			if (CirContainsPoint_(cir, vertArr[i])) {
				solveCollision_();
				return true;
			}
			if (CirCrossEdge_(cir, vertArr[(i+1)%4], vertArr[i])) {
				solveCollision_();
				return true;
			}
		}
		return false;
	}
	bool DefaultCollisionSolver::calcCollision_(Rectangle * rect1, Rectangle * rect2)
	{
		Point vertArr1[4];
		Point vertArr2[4];
		rect1->findVertices_(vertArr1);
		rect2->findVertices_(vertArr2);
		//const Point* vertArr1 = rect1->findVertices_();
		//const Point* vertArr2 = rect2->findVertices_();
		x::Counter<3> nCol;
		iter(i, 0, 3) {
			/*if (RectContainsPoint_(vertArr1, vertArr2[i])) {
				swapSeparate_ = false;
				solveCollision_();
				if (++nCol) break;
			}
			if (RectContainsPoint_(vertArr2, vertArr1[i])) {
				swapSeparate_ = true;
				solveCollision_();
				if (++nCol) break;
			}*/
			if (RectContainsPoint_(vertArr1, position_2, vertArr2[i])) {
				swapSeparate_ = false;
				solveCollision_();
				if (++nCol) break;
			}
			if (RectContainsPoint_(vertArr2, position_1, vertArr1[i])) {
				swapSeparate_ = true;
				solveCollision_();
				if (++nCol) break;
			}
		}
		swapSeparate_ = false;
		return nCol > 0;
	}

	DefaultCollisionSolver::~DefaultCollisionSolver()
	{
		/*--obj1_->nUsers;
		--obj2_->nUsers;*/
	}

}


#pragma region COLLIDER_UNDEFAULT_MACROS
#undef bound_1 
#undef bound_2 
#undef _r
#undef mass_1 
#undef mass_2 
#undef _m
#undef position_1 
#undef position_2 
#undef _P
#undef velocity_1 
#undef velocity_2 
#undef _v
#undef angularVelocity_1 
#undef angularVelocity_2 
#undef _av
#undef angle_1
#undef angle_2
#undef _an 
#undef inertiaMoment_1 
#undef inertiaMoment_2
#undef _I
#undef COR_1 
#undef COR_2 
#undef _COR
#undef force_1
#undef force_2
#undef torque_1
#undef torque_2
#undef _isCir
#undef _isRect
#pragma endregion