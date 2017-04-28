#ifndef PHYSICAL_COLLIDER_H
#define PHYSICAL_COLLIDER_H

#include "CollisionSolver.h"
#include "RigidRectangle.h"
#include "RigidCircle.h"

namespace phs
{
	class DefaultCollisionSolver: public CollisionSolver
	{
		//G_OBJECT;

		template<typename T1 = RigidBody, typename T2 = RigidBody>
		using CollisionFunc = bool(DefaultCollisionSolver::*)(T1*, T2*);

		bool swapSeparate_;
		Point colPos_;
		Vector colDir_;
		RigidBody* object1_;
		RigidBody* object2_;

		void separate_();
		void solveStaticCollision_();
		void solveDynamicCollision_();
		void calcFriction_();
		void solveCollision_();

		bool calcCollision_(Circle* obj1, Circle* obj2);
		bool calcCollision_(Rectangle* obj1, Circle* obj2);
		bool calcCollision_(Circle* cir, Rectangle* rect);
		bool calcCollision_(Rectangle* rect1, Rectangle* rect2);

		bool RectContainsPoint_(const Point vertArr[4], Point const& center, Point const& P);
		bool matchingCollisionFunc_();
		//bool RectContainsPoint_(const Point vertArr[4], Point const& P);
		bool CirCrossEdge_(Circle* cir, Point const& A, Point const& B);
		bool CirContainsPoint_(Circle* cir, Point const& P);

		bool bothStatic_() const;
		bool bothStopped_() const;
		bool bothValid_() const;
		bool relationsDenoteInclusion_(int relArr[4]) const;
		bool collisionGroupsOverlap_() const;
		basic_t responseCoefficient_(Vector const& colVersor, Vector const& colR1, Vector const& colR2);

		void setObjects_(RigidBody* obj1, RigidBody* obj2);
		bool boundsCollide_();

		static constexpr CollisionFunc<> colFuncs_[2][2]
		{
			{
				CollisionFunc<>(CollisionFunc<Circle,Circle>(&DefaultCollisionSolver::calcCollision_)),
				CollisionFunc<>(CollisionFunc<Circle,Rectangle>(&DefaultCollisionSolver::calcCollision_))},
			{
				CollisionFunc<>(CollisionFunc<Rectangle,Circle>(&DefaultCollisionSolver::calcCollision_)),
				CollisionFunc<>(CollisionFunc<Rectangle,Rectangle>(&DefaultCollisionSolver::calcCollision_))}
		};

	public:
		static constexpr basic_t DEFAULT_MIN_COL_DIR_LENGTH = 0.0001;
		static basic_t minColDirLength;

		DefaultCollisionSolver();
		DefaultCollisionSolver(DefaultCollisionSolver const&);
		DefaultCollisionSolver(DefaultCollisionSolver&&) = delete;
		DefaultCollisionSolver(RigidBody* obj1, RigidBody* obj2);

		void process(RigidBody* o1, RigidBody* o2) override;
		
		~DefaultCollisionSolver();
	};

	inline bool DefaultCollisionSolver::calcCollision_(Rectangle* obj1, Circle* obj2)
	{
		swapSeparate_ = true;
		return calcCollision_(obj2, obj1);
	}
}
#endif
