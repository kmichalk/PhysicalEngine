#include "Material.h"
#include <limits>

#define SET_DEFAULT_MATERIAL const PhysicalProp PhysicalProp::
#define SET_DEFAULT_APPEARANCE const Appearance Appearance::

PhysicalProp::PhysicalProp():
	density{Material::defaults[Material::DEFAULT].physical.density}, 
	friction{Material::defaults[Material::DEFAULT].physical.friction},
	restitution{Material::defaults[Material::DEFAULT].physical.restitution}
{
}

PhysicalProp::PhysicalProp(basic_t density, basic_t friction, basic_t restitution):
	density{density}, friction{friction}, restitution{restitution}
{
}

//PhysicalProp PhysicalProp::getDefault(Default num)
//{
//	return *defaults_[(size_t)num];
//}

Appearance::Appearance():
	fillColor{Material::defaults[Material::DEFAULT].appearance.fillColor},
	outlineColor{Material::defaults[Material::DEFAULT].appearance.outlineColor},
	outline{Material::defaults[Material::DEFAULT].appearance.outline}
{
}

Appearance::Appearance(sf::Color fillColor):
	fillColor{fillColor},
	outlineColor{Material::defaults[Material::DEFAULT].appearance.outlineColor},
	outline{Material::defaults[Material::DEFAULT].appearance.outline}
{
}

Appearance::Appearance(sf::Color fillColor, sf::Color outlineColor, float outline):
	fillColor{fillColor},
	outlineColor{outlineColor},
	outline{outline}
{
}

//Appearance Appearance::getDefault(Default num)
//{
//	return *defaults_[(size_t)num];
//}
//
//SET_DEFAULT_MATERIAL DEFAULT	{1.0, 0.5, 0.5};
//SET_DEFAULT_MATERIAL STEEL		{7.85, 0.5, 0.65};
//SET_DEFAULT_MATERIAL GOLD		{19.3, 0.5, 0.1};
//SET_DEFAULT_MATERIAL ICE		{0.9, 0.05, 0.05};
//SET_DEFAULT_MATERIAL MASSIVE	{100, 0.1, 0.5};
//SET_DEFAULT_MATERIAL HEAVY		{2000, 0.1, 0.5};
//SET_DEFAULT_MATERIAL WOOD		{0.6, 0.4, 0.4};
//SET_DEFAULT_MATERIAL RUBBER		{1.5, 1.5, 0.85};
//SET_DEFAULT_MATERIAL GLASS		{2.5, 0.2, 0.5};
//SET_DEFAULT_MATERIAL STONE		{2.4, 0.9, 0.2};
//SET_DEFAULT_MATERIAL WIREFRAME	{0.4, 0.4, 0.7};
//
//SET_DEFAULT_APPEARANCE DEFAULT	{{255,255,255},	{255,255,255},	-0.0f};
//SET_DEFAULT_APPEARANCE STEEL	{{180,180,180},	{145,145,145},	-2.0f};
//SET_DEFAULT_APPEARANCE GOLD		{{255,240,125},	{255,220,105},	-2.0f};
//SET_DEFAULT_APPEARANCE ICE		{{205,255,255},	{155,255,255},	-2.5f};
//SET_DEFAULT_APPEARANCE MASSIVE	{{100,0,100},	{155,0,75},		-3.0f};
//SET_DEFAULT_APPEARANCE HEAVY	{{100,0,0},		{155,0,0},		-3.0f};
//SET_DEFAULT_APPEARANCE WOOD		{{220,160,75},	{200,150,70},	-2.0f};
//SET_DEFAULT_APPEARANCE RUBBER	{{255,155,205},	{255,125,185},	-3.0f};
//SET_DEFAULT_APPEARANCE GLASS	{{245,250,255},	{255,255,255},	-1.5f};
//SET_DEFAULT_APPEARANCE STONE	{{130,130,130},	{100,100,100},	-2.0f};
//SET_DEFAULT_APPEARANCE WIREFRAME{{0,0,0,0},		{145,145,145},	-2.0f};
//
//const PhysicalProp const* PhysicalProp::defaults_[11]
//{
//	&DEFAULT,
//	&STEEL  ,
//	&GOLD   ,
//	&ICE	,
//	&MASSIVE,
//	&HEAVY  ,
//	&WOOD   ,
//	&RUBBER ,
//	&GLASS  ,
//	&STONE  ,
//	&WIREFRAME
//};
//
//const Appearance const* Appearance::defaults_[11]
//{
//	&DEFAULT,
//	&STEEL  ,
//	&GOLD   ,
//	&ICE	,
//	&MASSIVE,
//	&HEAVY  ,
//	&WOOD   ,
//	&RUBBER ,
//	&GLASS  ,
//	&STONE	,
//	&WIREFRAME
//};

const Material Material::defaults[11]
{
	{{1.0, 0.5, 0.5},	{{255,255,255},	{255,255,255},	-0.0f}},	//DEFAULT	
	{{7.85, 0.5, 0.55},	{{180,180,180},	{145,145,145},	-2.0f}},	//STEEL	
	{{19.3, 0.5, 0.1},	{{255,240,125},	{255,220,105},	-2.0f}},	//GOLD		
	{{0.9, 0.05, 0.05},	{{205,255,255},	{155,255,255},	-2.5f}},	//ICE		
	{{100, 0.1, 0.5},	{{100,0,100},	{155,0,75},		-3.0f}},	//MASSIVE	
	{{2000, 0.1, 0.5},	{{100,0,0},		{155,0,0},		-3.0f}},	//HEAVY	
	{{0.6, 0.4, 0.4},	{{220,160,75},	{200,150,70},	-2.0f}},	//WOOD		
	{{1.5, 1.5, 0.85},	{{255,155,205},	{255,125,185},	-3.0f}},	//RUBBER	
	{{2.5, 0.2, 0.5},	{{245,250,255},	{255,255,255},	-1.5f}},	//GLASS	
	{{2.4, 0.9, 0.2},	{{130,130,130},	{100,100,100},	-2.0f}},	//STONE	
	{{0.4, 0.4, 0.7},	{{0,0,0,0},		{145,145,145},	-2.0f}}		//WIREFRAME
};

#undef SET_DEFAULT_MATERIAL
#undef SET_DEFAULT_APPEARANCE

Material::Material(PhysicalProp const & physical, Appearance const & appearance):
	physical{physical}, appearance{appearance}
{
}
