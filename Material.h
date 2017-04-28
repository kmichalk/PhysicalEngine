#ifndef MATERIAL_H
#define MATERIAL_H

#include "SFML\Graphics.hpp"

using basic_t = double;

class Appearance
{
	//static const Appearance const* defaults_[11];

public:
	sf::Color fillColor;
	sf::Color outlineColor;
	float outline;

	Appearance();
	Appearance(Appearance const&) = default;
	Appearance(Appearance &&) = default;
	Appearance(sf::Color fillColor);
	Appearance(sf::Color fillColor, sf::Color outlineColor, float outline);

	Appearance& operator=(Appearance const&) = default;
	/*enum class Default
	{
		DEFAULT,
		STEEL,
		GOLD,
		ICE,
		MASSIVE,
		HEAVY,
		WOOD,
		RUBBER,
		GLASS,
		STONE,
		WIREFRAME
	};

	static Appearance getDefault(Default num);

	static const Appearance DEFAULT;
	static const Appearance STEEL;
	static const Appearance GOLD;
	static const Appearance ICE;
	static const Appearance MASSIVE;
	static const Appearance HEAVY;
	static const Appearance WOOD;
	static const Appearance RUBBER;
	static const Appearance GLASS;
	static const Appearance STONE;
	static const Appearance WIREFRAME;*/

	~Appearance() = default;
};

class PhysicalProp
{
	static const PhysicalProp const* defaults_[11];

public:
	basic_t density;
	basic_t friction;
	basic_t restitution;

	PhysicalProp();
	PhysicalProp(PhysicalProp const&) = default;
	PhysicalProp(PhysicalProp &&) = default;
	PhysicalProp(basic_t density, basic_t friction, basic_t restitution);

	PhysicalProp& operator=(PhysicalProp const&) = default;

	/*enum class Default
	{
		DEFAULT,
		STEEL,
		GOLD,
		ICE,
		MASSIVE,
		HEAVY,
		WOOD,
		RUBBER,
		GLASS,
		STONE,
		WIREFRAME
	};

	static PhysicalProp getDefault(Default num);

	static const PhysicalProp DEFAULT;
	static const PhysicalProp STEEL;
	static const PhysicalProp GOLD;
	static const PhysicalProp ICE;
	static const PhysicalProp MASSIVE;
	static const PhysicalProp HEAVY;
	static const PhysicalProp WOOD;
	static const PhysicalProp RUBBER;
	static const PhysicalProp GLASS;
	static const PhysicalProp STONE;
	static const PhysicalProp WIREFRAME;*/
	
	~PhysicalProp() = default;
};

class Material
{
public:
	PhysicalProp physical;
	Appearance appearance;

	Material(PhysicalProp const& physical, Appearance const& appearance);

	enum DefNum
	{
		DEFAULT,
		STEEL,
		GOLD,
		ICE,
		MASSIVE,
		HEAVY,
		WOOD,
		RUBBER,
		GLASS,
		STONE,
		WIREFRAME
	};

	static const Material defaults[11];
};

#endif