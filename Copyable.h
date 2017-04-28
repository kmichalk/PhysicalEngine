#pragma once

class Copyable
{
public:
	virtual Copyable* copy() const abstract;

	virtual ~Copyable();
};
