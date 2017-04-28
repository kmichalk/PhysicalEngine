#pragma once

#include "Event.h"
#include "phsObject.h"


class CreateObject: public Executable
{
protected:
	phs::Object* template_;
	Point* position_;
	
public:
	CreateObject(Executable* consequence = nullptr);

	virtual void execute() override;
};
