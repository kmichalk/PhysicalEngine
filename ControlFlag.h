#pragma once

#include "Switchable.h"

namespace game
{
	class ControlFlag: public Switchable
	{
	protected:
		ControlFlag(bool enabled = false);
	};
}
