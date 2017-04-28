#include "ChainedExecutable.h"

ChainedProcedure::ChainedProcedure(Procedure * consequence):
	consequence_{consequence}
{
}

ChainedProcedure::ChainedProcedure(ChainedProcedure const & other):
	consequence_{other.consequence_ ? other.consequence_->copy() : nullptr}
{
}

ChainedProcedure::ChainedProcedure(ChainedProcedure && other):
	consequence_{other.consequence_}
{
	other.consequence_ = nullptr;
}

void ChainedProcedure::execute()
{
	if (consequence_)
		consequence_->execute();
}

ChainedProcedure::~ChainedProcedure()
{
	if (consequence_)
		delete consequence_;
}
