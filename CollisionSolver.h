#ifndef _COLLISION_SOLVER_H_
#define _COLLISION_SOLVER_H_

#include "Object.h"

namespace phs
{
	class RigidBody;

	class CollisionSolver
	{		
	public:
		CollisionSolver();
		//virtual bool boundsCollide(phs::RigidBody* o1, phs::RigidBody* o2) abstract;
		virtual void process(phs::RigidBody* o1, phs::RigidBody* o2) abstract;
	};
}
#endif //_COLLISION_SOLVER_H_
