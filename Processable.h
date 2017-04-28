#pragma once

class Processable
{
public:
	virtual void process() abstract;

	virtual ~Processable();
};
