#include "CollisionGroupManager.h"

bool phs::CollisionGroupManager::collides(CollisionGroupManager const & other) const
{
	return enabled && other.enabled && ((*this) & other);
}

bool phs::CollisionGroupManager::groupsOverlap(CollisionGroupManager const & other) const
{
	return (*this) & other;
}
