#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include <atomic>
#include "crd.h"
#include "error.h"
#include "abstract.h"
#include "Switchable.h"
#include "Object.h"

class UseManager
{
	std::atomic<unsigned> nUsers_; //TODO: optimize atomics, maybe 

public:
	__forceinline UseManager():
		nUsers_{0}
	{
	}

	__forceinline unsigned operator--()
	{
		if (nUsers_ == 0)
			throw x::error<UseManager>{};
		return --nUsers_;
	}

	__forceinline unsigned operator++()
	{
		return ++nUsers_;
	}

	__forceinline unsigned operator()() const
	{
		return nUsers_;
	}
};

using basic_t = double;
using Vector = crd<basic_t>;
using Point = crd<basic_t>;
using Size = crd<basic_t>;

namespace phs
{
	class DefaultCollisionSolver;
	class QuadTree;
	class PhysicalEngine;
}

namespace game
{
	class Application;

	class Element: virtual public Object
	{
		G_OBJECT;

		volatile bool alive_ = true;

	protected:
		static phs::PhysicalEngine* enginePtr_;
		static game::Application* appPtr_;

	public:
		struct TypeProperties
		{
			bool const locatable	: 1;
			bool const physical		: 1;
			bool const drawable		: 1;
			bool const emitter		: 1;
			bool const area			: 1;

			TypeProperties() = delete;
			TypeProperties(TypeProperties const&) = default;
			TypeProperties(TypeProperties&&) = default;
			constexpr TypeProperties(
				bool locatable,
				bool physical, 
				bool drawable, 
				bool emitter, 
				bool area);
			~TypeProperties() = default;
		};

		friend class phs::DefaultCollisionSolver;
		friend class phs::QuadTree;

		TypeProperties properties;
		UseManager nUsers;

		static void setEngine(phs::PhysicalEngine* engine);
		static void setApplication(game::Application& app);

		Element(Element const& other);
		Element(TypeProperties const& properties);

		//virtual x::dynamic_ptr<game::Element> copy() const abstract;
		void virtual process();
		bool virtual isVisible() const;
		bool isAlive() const;
		void kill();

		virtual ~Element();
	};

	///////////////////////////////////////////////////////////////////////////////

	inline bool Element::isAlive() const
	{
		return alive_;
	}

	inline void Element::kill()
	{
		alive_ = false;
	}

	inline Element::~Element()
	{
	}

	constexpr Element::TypeProperties::TypeProperties(
		bool locatable,
		bool physical, 
		bool drawable, 
		bool emitter, 
		bool area)
		:
		locatable	{locatable},
		physical	{physical},
		drawable	{drawable},
		emitter		{emitter},
		area		{area}
	{
	}

}

#endif //GAME_ELEMENT_H
