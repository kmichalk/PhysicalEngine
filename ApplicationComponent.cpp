#include "ApplicationComponent.h"
#include "Application.h"


namespace game
{
	ApplicationComponent::ApplicationComponent(Application & parent):
		parent_{parent}
	{
		parent_.addComponent(this);
	}

	ApplicationComponent::~ApplicationComponent()
	{
	}
}