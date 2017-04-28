#pragma once

#include "TimePeriod.h"
#include "Processable.h"


template<class _Type>
class TimedChange: public Processable
{
protected:
	Timer changeTimer_;
	TimePeriod updateTimer_;
	_Type& value_;

	TimedChange(_Type& value, double updatePeriod = DEFAULT_UPDATE_PERIOD);

	virtual void update_() abstract;

public:
	static constexpr double DEFAULT_UPDATE_PERIOD = 0.02;

	virtual void process() override;
	void reset();
};


///////////////////////////////////////////////////////////////////////////////


template<class _Type>
inline TimedChange<_Type>::TimedChange(_Type & value, double updatePeriod):
	changeTimer_{},
	updateTimer_{updatePeriod},
	value_{value}
{
}

template<class _Type>
inline void TimedChange<_Type>::process()
{
	if (updateTimer_.reached()) {
		updateTimer_.start();
		process();
	}
}

template<class _Type>
inline void TimedChange<_Type>::reset()
{
	changeTimer_.tic();
}

