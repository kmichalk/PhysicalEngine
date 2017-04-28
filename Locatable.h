#ifndef _LOCATABLE_H_
#define _LOCATABLE_H_

#include "defCrd.h"

namespace game
{
	class Locatable
	{
	public:
		Point virtual getPosition() const abstract;

		virtual ~Locatable();
	};
}

#endif //_LOCATABLE_H_
