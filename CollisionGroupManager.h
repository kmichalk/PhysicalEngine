#pragma once

#include "bitmanager.h"
#include "flag.h"

namespace phs
{
	constexpr unsigned COLLISION_GROUP_NUMBER = 16;

	class CollisionGroupManager: private x::bitmanager<COLLISION_GROUP_NUMBER>
	{
	public:
		x::flag enabled;

		bool collides(CollisionGroupManager const& other) const;
		bool groupsOverlap(CollisionGroupManager const& other) const;

		inline void setGroup(unsigned group, bool value)
		{
			setBit(group, value);
		}
	};
}
