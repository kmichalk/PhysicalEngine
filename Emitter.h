#ifndef GAME_EMITTER_OBJECT_H
#define GAME_EMITTER_OBJECT_H

#include "GameObject.h"
#include "Timer.h"
#include "abstract.h"
#include "ObjectFactory.h"

namespace game
{
	class ObjectOrganizer;
	class ObjectFactory;
	
	class Emitter:
		public GameObject
	{
		G_OBJECT;
	public:
		class Pattern
		{
		protected:
			bool finished_;
		public:
			Pattern();
			Pattern(Pattern const&);

			bool finished() const;
			virtual x::dynamic_ptr<GameObject> get() abstract;
		};


		class SingleObject:
			public Pattern
		{
			x::Abstract<GameObject> emittedObject_;
		public:
			SingleObject(SingleObject const& other);
			SingleObject(x::Abstract<GameObject> const& object);

			virtual x::dynamic_ptr<GameObject> get() override;
		};


		class Sequence:
			public Pattern
		{
		protected:
			using ElemInitList = std::initializer_list<x::Abstract<GameObject>>;
			x::vector<x::Abstract<GameObject>> sequence_;
		public:
			Sequence(Sequence const& other);
			Sequence(ElemInitList objects);

			virtual x::dynamic_ptr<GameObject> get() abstract override;
		};


		class FiniteSequence:
			public Sequence
		{
			using SeqIter = x::vector<x::Abstract<GameObject>>::iterator;

			SeqIter objIter_;

		public:
			FiniteSequence(FiniteSequence const& other);
			FiniteSequence(ElemInitList objects);

			virtual x::dynamic_ptr<GameObject> get() override;
		};


		class LoopSequence:
			public Sequence
		{
			using SeqIter = x::vector<x::Abstract<GameObject>>::iterator;

			SeqIter objIter_;

		public:
			LoopSequence(LoopSequence const& other);
			LoopSequence(ElemInitList objects);

			virtual x::dynamic_ptr<GameObject> get() override;
		};


		/*class Random:
			public Pattern
		{
		public:
			virtual x::dynamic_ptr<GameObject> get() override;
		};*/
		bool finishedPeriod_();

	protected:
		static constexpr TypeProperties			OBJECT_TYPE_PROPERTIES_ = {true,false,false,true,false};
		static const x::Abstract<sf::Shape>		EMPTY_SHAPE_;
		static const x::Abstract<phs::RigidBody>	EMPTY_PHYSICAL_OBJECT_;
	
		bool paused_;
		Timer emitTimer_;
		double emitPeriod_;
		x::Abstract<Pattern> pattern_;
		game::ObjectOrganizer& organizer_;
		x::Abstract<game::DynamicsApplier> initialDynamics_;
	
	public:
		Emitter(
			double emitPeriod,
			x::Abstract<Pattern> const&					pattern,
			game::ObjectOrganizer&						organizer,
			x::Abstract<game::DynamicsApplier> const&	initialDynamics,
			x::Abstract<sf::Shape> const&				shape		= EMPTY_SHAPE_,
			x::Abstract<phs::RigidBody> const&				phsObject	= EMPTY_PHYSICAL_OBJECT_,
			GameObject::TypeProperties const&				properties	= OBJECT_TYPE_PROPERTIES_);

		void virtual process() override;
		void emit() const;
		void start();
		void pause();
	};

	inline bool Emitter::Pattern::finished() const
	{
		return finished_;
	}
}
#endif //GAME_EMITTER_OBJECT_H
