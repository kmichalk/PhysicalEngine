#include "Object.h"



void * Object::cast_(x::num_t type)
{
	return typenum(Object) == type ? this : nullptr;
}

Object * Object::getThis()
{
	return this;
}

Object const * Object::getThis() const
{
	return this;
}

Copyable * Object::copy() const
{
	return new Object{*this};
}

char const* Object::getClassName() const
{
	return typeid(this).name();
}

Object::~Object()
{
}