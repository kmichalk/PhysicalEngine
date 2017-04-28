#pragma once

#include "EventHandler.h"
#include "KeyEvent.h"
#include "Function.h"

namespace game
{
	class KeyEventHandler: public EventHandler
	{
		int findPositionByKey_(WKey key) const;

	public:
		using EventHandler::EventHandler;

		template<class _Type, class _Owner>
		void setShortcut(WKey key, _Type* object, void(_Owner::* member)());
		template<class _Func>
		void setShortcut(WKey key, _Func&& func);
		void setShortcut(WKey key, Procedure* procedure);

		void setKeyEnabled(WKey key, bool value);

		void removeShortcut(WKey key);
		KeyEvent* findByKey(WKey key) const;
	};

	///////////////////////////////////////////////////////////////////////////////

	
	template<class _Type, class _Owner>
	inline void KeyEventHandler::setShortcut(WKey key, _Type* object, void(_Owner::* member)())
	{
		addReliant(new KeyPressEvent{key, new Function<void()>{object,member}});
	}

	template<class _Func>
	inline void KeyEventHandler::setShortcut(WKey key, _Func && func)
	{
		addReliant(new KeyPressEvent{key, new Function<void()>{func}});
	}
}