#pragma once

#include "Copyable.h"


template<class...>
class Executable;


template<class _Ret, class... _Args>
class Executable<_Ret(_Args...)>: public Copyable
{
public:
	virtual Executable<void()>* copy() const abstract override;
	virtual _Ret execute(_Args... args) abstract;
};


using Procedure = Executable<void()>;
