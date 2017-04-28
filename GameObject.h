#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "DrawableShape.h"
#include "RigidCircle.h"
#include "RigidRectangle.h"
#include "Object.h"

namespace game
{
	class GameObject: public DrawableShape
	{
		G_OBJECT;
	

	protected:
	public:
		static constexpr Element::TypeProperties OBJECT_TYPE_PROPERTIES_={
			true,true,true,false,false};		


		x::Abstract<phs::RigidBody> physicalObject_;

		GameObject(GameObject const& other);

		GameObject(x::Abstract<sf::Shape> const& shapePtr,
			x::Abstract<phs::RigidBody> const& phsObjPtr,
			Element::TypeProperties const&	properties = OBJECT_TYPE_PROPERTIES_);

		void virtual applyDefaults(Material::DefNum);
		void virtual refresh() override;
		//void virtual setPosition(Point const& position) override;
		Point virtual getPosition() const override;
		/*void setVelocity(Vector const& velocity);
		Vector getVelocity() const;
		void setAngle(basic_t angle);
		basic_t getAngle() const;*/
	};

	class CircleObject:
		public game::GameObject
	{
	public:
		//CircleObject();
		CircleObject(basic_t radius, Point const& position, basic_t angle = 0.0);
	};

	class RectangleObject:
		public game::GameObject
	{
	public:
		//RectangleObject();
		RectangleObject(Size const& size, Point const& position, basic_t angle = 0.0);
	
	};
}
#endif //GAME_OBJECT_H
