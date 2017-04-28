#pragma once

#include "Drawable.h"

namespace game
{
	class DrawableShape:
		public Drawable
	{
		G_OBJECT;
	public:
		x::Abstract<sf::Shape> shape_;

	protected:
		void virtual centerOrigin_();

	public:
		DrawableShape(DrawableShape const& other);
		DrawableShape(x::Abstract<sf::Shape> const& shapePtr,
			Element::TypeProperties const& properties);

		void virtual setPosition(Point const& position) override;
		Point virtual getPosition() const override;
		//virtual x::dynamic_ptr<game::Element> copy() const override;
		void virtual DrawableShape::draw(
			sf::RenderTarget &	target,
			sf::RenderStates	states = sf::RenderStates::Default) const override;

		void apply(Appearance const& appearance);

		sf::Shape* getShape();
	};
}
