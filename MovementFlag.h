#pragma once

#include "ControlFlag.h"
#include "defCrd.h"



namespace game
{
	class MovementFlag: public ControlFlag
	{
		static const Vector DIRECTION_TYPE_VERSORS_[4];
		static const Vector DIRECTION_MAP_[2][2][2][2];

	public:
		enum class Type: byte
		{
			UP, DOWN, LEFT, RIGHT
		};

		static Vector sumDirections(bool up, bool down, bool left, bool right);

		const Type type;
		Vector direction;

		MovementFlag(Type type);
		MovementFlag(MovementFlag const& other);
	};

	///////////////////////////////////////////////////////////////////////////////

	inline Vector MovementFlag::sumDirections(bool up, bool down, bool left, bool right)
	{
		return DIRECTION_MAP_[up][down][left][right];
	}

}
