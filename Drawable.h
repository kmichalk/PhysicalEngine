#ifndef GAME_DRAWABLE_ELEMENT_H
#define GAME_DRAWABLE_ELEMENT_H

#include "Element.h"
#include "locatable.h"
#include "SFML\Graphics.hpp"
#include "auto_cast.h"
#include "Material.h"

namespace game
{
	class Drawable:
		public Element,
		public sf::Drawable,
		public Locatable
	{
		G_OBJECT;

	protected:
		volatile bool visible_;

	public:
		Drawable(Drawable const& other);
		Drawable(Element::TypeProperties const& properties);
		Drawable(bool visible, Element::TypeProperties const& properties);

		//virtual x::dynamic_ptr<game::Element> copy() const override;
		void draw(
			sf::RenderTarget &	target, 
			sf::RenderStates	states = sf::RenderStates::Default) const abstract override;
		bool virtual isVisible() const override;
		void virtual refresh();
		void virtual setPosition(Point const& position) abstract;
		Point virtual getPosition() const abstract override;
	};

	

	//template<class ShapeType>
	//class DrawableShape;

	//template<>
	//class DrawableShape<sf::CircleShape>: 
	//	public game::Drawable,
	//	public sf::CircleShape
	//{
	//protected:
	//public:
	//	DrawableShape():
	//		game::Drawable{(sf::Shape&)(*this)},
	//		sf::CircleShape{}
	//	{
	//	}

	//	DrawableShape(basic_t radius, sf::Vector2f position, basic_t angle = 0.0):
	//		game::Drawable{(sf::Shape&)(*this)},
	//		sf::CircleShape{radius}
	//	{
	//		setOrigin(radius,radius);
	//		setPosition(position.x, position.y);
	//		setRotation(angle);
	//	}

	//	DrawableShape(sf::CircleShape const& shape):
	//		game::Drawable{(sf::Shape&)(*this)},
	//		sf::CircleShape{shape}
	//	{
	//		setOrigin(getRadius(), getRadius());
	//	}

	//	/*void virtual draw(sf::RenderTarget& target,
	//		sf::RenderStates states = sf::RenderStates::Default) const override
	//	{
	//		if (visible_) {
	//			rem_const(this)->refresh();
	//			target.draw(*this);
	//		}
	//	}*/
	//};

	//template<>
	//class DrawableShape<sf::RectangleShape>:
	//	public game::Drawable,
	//	public sf::RectangleShape
	//{
	//public:
	//	DrawableShape():
	//		game::Drawable{(sf::Shape&)(*this)},
	//		sf::RectangleShape{}
	//	{
	//	}

	//	DrawableShape(Size size, sf::Vector2f position, basic_t angle = 0.0):
	//		game::Drawable{(sf::Shape&)(*this)},
	//		sf::RectangleShape{{(float)size.x,(float)size.y}}
	//	{
	//		setOrigin(size.x/2, size.y/2);
	//		setPosition(position.x, position.y);
	//		setRotation(angle);
	//	}

	//	DrawableShape(sf::RectangleShape const& shape):
	//		game::Drawable{(sf::Shape&)(*this)},
	//		sf::RectangleShape{shape}
	//	{
	//		setOrigin(getSize()/2.0f);
	//	}

	///*	void virtual draw(sf::RenderTarget& target,
	//		sf::RenderStates states = sf::RenderStates::Default) const override
	//	{
	//		if (visible_) {
	//			rem_const(this)->refresh();
	//			target.draw(*((sf::RectangleShape*)this));
	//		}
	//	}*/
	//};
}
#endif //GAME_DRAWABLE_ELEMENT_H
