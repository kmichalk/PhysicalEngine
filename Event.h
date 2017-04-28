#pragma once

#include "Task.h"
#include "Copyable.h"
#include "Executable.h"
#include "Switchable.h"

#undef KEY_EVENT

namespace game
{
	class Event: public Task
	{
		G_OBJECT;

	public:
		enum class Type {
			UNKNOWN, KEY_EVENT, TIMER_EVENT
		};

	protected:
		const Type type_;

		virtual Procedure* triggered_() abstract;

		Event(Type type = Type::UNKNOWN, TaskHandler* handler = nullptr);

	public:
		virtual void process() override;
		//virtual Event* copy() const abstract override;

		Type getType() const;
	};

	///////////////////////////////////////////////////////////////////////////////

	inline Event::Type Event::getType() const
	{
		return type_;
	}
}