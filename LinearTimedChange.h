#pragma once

#include "TimedChange.h"

template<class _Type>
class LinearTimedChange: public TimedChange<_Type>
{
	_Type beginValue_;
	_Type perSecond_;

public:
	LinearTimedChange(_Type& value, _Type changePerSecond);

	virtual void process() override;
};


///////////////////////////////////////////////////////////////////////////////


template<class _Type>
inline LinearTimedChange<_Type>::LinearTimedChange(_Type & value, _Type changePerSecond):
	TimedChange<_Type>(value),
	beginValue_{value},
	perSecond_{changePerSecond}
{
}

template<class _Type>
inline void LinearTimedChange<_Type>::process()
{
	value_ = beginValue_ + changeTimer_.toc()* perSecond_;
}
