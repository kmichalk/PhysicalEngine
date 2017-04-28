#include "TimePeriod.h"

TimePeriod::TimePeriod(double period):
	timer_{},
	period_{period},
	started_{false}
{
}

TimePeriod::TimePeriod(TimePeriod const & other):
	timer_{},
	period_{other.period_},
	started_{false}
{
}

void TimePeriod::start()
{
	timer_.tic();
	started_ = true;
}

bool TimePeriod::reached() const
{
	return timer_.toc() > period_;
}

bool TimePeriod::started() const
{
	return started_;
}

double TimePeriod::percentage() const
{
	if (!started_) return 0.0;
	double value = timer_.toc() / period_;
	return value < 1.0 ? value : 1.0;
}

double TimePeriod::getLength() const
{
	return period_;
}

