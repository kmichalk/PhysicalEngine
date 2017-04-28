#pragma once

#include "Executable.h"


class ChainedProcedure: virtual public Procedure
{
protected:
	Procedure* consequence_;

public:
	ChainedProcedure(Procedure* consequence = nullptr);
	ChainedProcedure(ChainedProcedure const& other);
	ChainedProcedure(ChainedProcedure&& other);

	virtual Procedure* copy() const abstract override;
	virtual void execute() override;
	virtual ~ChainedProcedure();
};
