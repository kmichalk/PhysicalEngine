#include "Emitter.h"
#include "ObjectOrganizer.h"

namespace game
{
	Emitter::Pattern::Pattern()
		:
		finished_{false}
	{
	}

	Emitter::Pattern::Pattern(Pattern const & other)
		:
		finished_{other.finished_}
	{
	}

	Emitter::SingleObject::SingleObject(SingleObject const & other)
		:
		Pattern			(other),
		emittedObject_	{other.emittedObject_}
	{
	}

	Emitter::SingleObject::SingleObject(x::Abstract<game::GameObject> const & object)
		:
		emittedObject_{object}
	{
	}

	x::dynamic_ptr<game::GameObject> Emitter::SingleObject::get()
	{
		return emittedObject_.copy();
	}

	Emitter::FiniteSequence::FiniteSequence(FiniteSequence const & other)
		:
		Sequence	(other),
		objIter_	{other.objIter_}
	{
	}

	Emitter::FiniteSequence::FiniteSequence(ElemInitList objects)
		:
		Sequence	{objects},
		objIter_	{sequence_, 0}
	{		
	}

	x::dynamic_ptr<game::GameObject> Emitter::FiniteSequence::get()
	{
		if (objIter_) {
			return (objIter_++)->copy();
		}
		else {
			finished_ = true;
			throw x::error<Emitter::Pattern>{};
		}
	}

	Emitter::LoopSequence::LoopSequence(LoopSequence const & other)
		:
		Sequence	(other),
		objIter_	{other.objIter_}
	{
	}

	Emitter::LoopSequence::LoopSequence(ElemInitList objects)
		:
		Sequence	{objects},
		objIter_	{sequence_,0}
	{
	}

	x::dynamic_ptr<game::GameObject> Emitter::LoopSequence::get()
	{
		return (objIter_++)->copy();
	}

	bool Emitter::finishedPeriod_()
	{
		if (emitTimer_.toc() > emitPeriod_) {
			emitTimer_.tic();
			return true;
		}
		return false;
	}

	Emitter::Emitter(
		double emitPeriod,
		x::Abstract<Pattern> const&					pattern,
		game::ObjectOrganizer&						organizer,
		x::Abstract<game::DynamicsApplier> const&	initialDynamics,
		x::Abstract<sf::Shape> const &				shape,
		x::Abstract<phs::RigidBody> const&				phsObject,
		GameObject::TypeProperties const &				properties)
		:
		GameObject			{shape, phsObject,properties},
		paused_			{false},
		emitPeriod_		{emitPeriod},
		organizer_		{organizer},
		initialDynamics_{initialDynamics},
		pattern_		{pattern}
	{
	}

	void Emitter::start()
	{
		if (paused_) 
			paused_ = false;			
		else 
			emitTimer_.tic();		
	}

	void Emitter::pause()
	{
		paused_ = true;
	}

	void Emitter::process()
	{
		if (isEnabled() && !pattern_->finished() && finishedPeriod_()) {
			try {
				auto emittedObject{pattern_->get()};
				initialDynamics_->apply(*emittedObject->physicalObject_);
				emittedObject->applyDefaults(Material::GOLD);
				organizer_.add(emittedObject);
			}
			catch (x::error<Emitter::Pattern>) {}
		}
	}

	void Emitter::emit() const
	{

	}

	const x::Abstract<sf::Shape>	Emitter::EMPTY_SHAPE_			= {};
	const x::Abstract<phs::RigidBody>	Emitter::EMPTY_PHYSICAL_OBJECT_ = {};

	Emitter::Sequence::Sequence(Sequence const & other)
		:
		Pattern		(other),
		sequence_	{other.sequence_}
	{
	}

	Emitter::Sequence::Sequence(ElemInitList objects):
		sequence_{objects}
	{
	}
}