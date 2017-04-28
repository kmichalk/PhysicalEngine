#include "MovementFlag.h"

namespace game
{
	MovementFlag::MovementFlag(Type type):
		type{type},
		direction{DIRECTION_TYPE_VERSORS_[(byte)type]}
	{
	}

	MovementFlag::MovementFlag(MovementFlag const & other):
		type{other.type}
	{
	}

	const Vector MovementFlag::DIRECTION_TYPE_VERSORS_[4] = {
		{0.0,1.0},
		{0.0,-1.0},
		{-1.0, 0.0},
		{1.0,0.0}
	};

	int arr[2][4] = {
		{
			1,2,3,4
		},{1,2,3,4}
	};

	static const double sq = sqrt(2.0) / 2.0;

	const Vector MovementFlag::DIRECTION_MAP_[2][2][2][2] = {
		{
			{
				{{0.0, 0.0}, {1.0, 0.0}},
				{{-1.0, 0.0}, {0.0, 0.0}}
			},
			{
				{{0.0, -1.0}, {sq, -sq}},
				{{-sq, -sq}, {0.0, -1.0}}
			}
		},
		{
			{
				{{0.0, 1.0}, {sq, sq}},
				{{-sq, sq}, {0.0, 1.0}}
			},
			{
				{{0.0, 0.0}, {1.0, 0.0}},
				{{-1.0, 0.0}, {0.0, 0.0}}
			}
		}
	};
}