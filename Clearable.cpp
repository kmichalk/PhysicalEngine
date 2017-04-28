#include "Clearable.h"

void Clearable::clear()
{
}

Clearable::~Clearable()
{
	clear();
}
