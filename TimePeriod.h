#pragma once

#include "Timer.h"

class TimePeriod
{
	mutable Timer timer_;
	double period_;
	volatile bool started_;

public:
	TimePeriod(double period);
	TimePeriod(TimePeriod const& other);

	void start();
	bool reached() const;
	bool started() const;
	double percentage() const;
	double getLength() const;
};
