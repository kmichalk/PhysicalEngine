#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "Element.h"
#include "locatable.h"
#include "MemberAbstract.h"

namespace game
{
	class Mouse:
		public game::Element,
		public game::Locatable
	{
		static constexpr Element::TypeProperties MOUSE_TYPE_PROPERTIES_ = {
			true,false,false,false,false};

	public:
		Mouse();

		Point virtual getPosition() const override;
		x::Abstract<Value<Point>> positionReference();
	};
}
#endif //_MOUSE_H_
