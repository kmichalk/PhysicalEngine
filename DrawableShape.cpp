#include "DrawableShape.h"
#include "PhysicalEngine.h"


namespace game
{
	void DrawableShape::centerOrigin_()
	{
		sf::FloatRect shapeBounds{shape_->getLocalBounds()};
		shape_->setOrigin(shapeBounds.width / 2.0f, shapeBounds.height / 2.0f);
	}

	DrawableShape::DrawableShape(DrawableShape const & other):
		Drawable(other),
		shape_{other.shape_}
	{
	}

	DrawableShape::DrawableShape(
		x::Abstract<sf::Shape> const& shapePtr,
		Element::TypeProperties const & properties)
		:
		game::Drawable{properties},
		shape_{shapePtr}
	{
	}

	void DrawableShape::setPosition(Point const& position)
	{
		//shape_->setPosition(parentEngine->dispPos(position));
	}

	Point DrawableShape::getPosition() const
	{
		return enginePtr_->realPos(shape_->getPosition());
	}

	//x::dynamic_ptr<game::Element> DrawableShape::copy() const
	//{
	//	return x::New<game::DrawableShape>{*this};
	//}

	void DrawableShape::draw(
		sf::RenderTarget &	target,
		sf::RenderStates	states) const
	{
		if (shape_ && visible_) {
			x::rem_const(this)->refresh();
			target.draw(*shape_);
		}
	}

	void DrawableShape::apply(Appearance const & appearance)
	{
		shape_->setFillColor(appearance.fillColor);
		shape_->setOutlineColor(appearance.outlineColor);
		shape_->setOutlineThickness(appearance.outline);
	}

	sf::Shape * DrawableShape::getShape()
	{
		return static_cast<sf::Shape*>(shape_);
	}
}
/*DrawableShape<sf::CircleShape>::DrawableShape(sf::CircleShape const & shape):
Element{true,false,false,false},
shape_{*(new sf::CircleShape{shape})}
{
}

void DrawableShape::refresh()
{
}*/