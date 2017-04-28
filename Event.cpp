#include "Event.h"

namespace game
{
	//Event::Event(Procedure * consequence):
	//	consequence_{consequence}
	//{
	//}
	//
	//Event::Event(Event const & other):
	//	consequence_{other.consequence_}
	//{
	//}



	Event::Event(Type type, TaskHandler * handler):
		Task{handler},
		type_{type}
	{
	}

	void Event::process()
	{
		if (auto action = triggered_())
			action->execute();		
	}


	/*void Event::process()
	{
		
	}*/

}