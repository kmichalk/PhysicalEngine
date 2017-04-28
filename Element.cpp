#include "Element.h"

namespace game
{
	void Element::setEngine(phs::PhysicalEngine * engine)
	{
		enginePtr_ = engine;
	}

	void Element::setApplication(game::Application & app)
	{
		appPtr_ = &app;
	}

	Element::Element(Element const & other):
		properties{other.properties}
	{
	}

	Element::Element(TypeProperties const & properties):
		properties{properties}
	{
	}

	/*Element::Element(Point const & position, basic_t angle, bool drawable, bool physical, bool emitter, bool area):
		drawable{drawable}, physical{physical}, emitter{emitter}, area{area},
		dynamics.position{position},
		angularDynamics.angle{angle}
	{
	}*/

	bool Element::isVisible() const
	{
		return false;
	}

	void Element::process()
	{
	}

	
	Application* Element::appPtr_ = nullptr;
}