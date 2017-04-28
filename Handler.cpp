#include "Handler.h"

namespace game
{
	/*Handler<Reliant>::Handler(x::vector<Reliant*>& reliants):
		reliantsRef_{reliants}
	{
	}

	void Handler<Reliant>::clear()
	{
		reliantsRef_.delete_each();
		reliantsRef_.clear();
	}

	size_t Handler<Reliant>::getReliantsNumber() const
	{
		return reliantsRef_.size();
	}


	bool Handler<Reliant>::hasReliant(Reliant * reliant) const
	{
		return (bool)reliantsRef_.find(reliant);
	}


	void Handler<Reliant>::addReliant(Reliant * reliant)
	{
		if (reliant && reliant->getHandler() == this && !hasReliant(reliant))
			reliantsRef_.push_back(reliant);
	}


	void Handler<Reliant>::detachReliant(Reliant * reliant)
	{
		reliantsRef_.remove(reliant);
	}

	Handler<Reliant>::~Handler()
	{
		clear();
	}
*/
}
