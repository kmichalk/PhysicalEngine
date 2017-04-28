#include "Drawable.h"
#include "PhysicalEngine.h"

namespace game
{
	Drawable::Drawable(game::Drawable const & other):
		Element(other),
		visible_{(bool)other.visible_}
	{
	}

	Drawable::Drawable(
		Element::TypeProperties const & properties)
		:
		Element{properties},
		visible_{true}
	{
	}

	Drawable::Drawable(
		bool visible, 
		Element::TypeProperties const & properties)
		:
		Element{properties},
		visible_{visible}
	{
	}

	//x::dynamic_ptr<game::Element> Drawable::copy() const
	//{
	//	return x::New<Drawable>{x::ref<const game::Drawable>(*this)};
	//}

	void Drawable::refresh()
	{
	}

	bool Drawable::isVisible() const
	{
		return visible_;
	}

}