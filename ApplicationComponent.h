#ifndef APPLICATION_COMPONENT_H
#define APPLICATION_COMPONENT_H

#include "Object.h"

namespace game
{
	class Application;

	class ApplicationComponent: virtual public Object
	{
		G_OBJECT;
		
	protected:
		game::Application& parent_;
	public:
		ApplicationComponent() = delete;
		ApplicationComponent(Application& parent);

		virtual ~ApplicationComponent();
	};
}
#endif //APPLICATION_COMPONENT_H
