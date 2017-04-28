#ifndef _GAME_EVENT_H_
#define _GAME_EVENT_H_

#include "keyevent.h"
#include "Timer.h"
#include "Closeable.h"

namespace game
{
	class GameEvent: public Event, public Closeable
	{
	protected:
		bool volatile active_;
		bool volatile alive_;

		GameEvent() = delete;
		GameEvent(x::Callable<void()> const& action);
		virtual void deactivate_();
		virtual void activate_();
		virtual bool trigger() abstract override;

	public:
		virtual bool isClosed() const override;
		virtual void close() override;

		void setActive(bool value);
	};

}

#endif //_GAME_EVENT_H_