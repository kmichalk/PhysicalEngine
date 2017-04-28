#pragma once

#include "ThreadProcess.h"
#include "Reliant.h"

namespace game
{
	//class Reliant;

	//template<class = Reliant>
	//class Handler;


	//template<>
	//class Handler<Reliant>: public ThreadProcess
	//{
	//	x::vector<Reliant*>& reliantsRef_;

	//protected:
	//	Handler(x::vector<Reliant*>& reliants);

	//public:
	//	virtual void process() abstract override;
	//	virtual void clear() override;

	//	size_t getReliantsNumber() const;
	//	bool hasReliant(Reliant* reliant) const;
	//	void addReliant(Reliant* reliant);
	//	void detachReliant(Reliant* reliant);

	//	virtual ~Handler();
	//};

	/////////////////////////////////////////////////////////////////////////////////
	//
	//template<class _Type>
	//class Handler: public Handler<Reliant>
	//{
	//	static_assert(std::is_base_of<Reliant, _Type>::value,
	//		"Handled objects type must derive from HandledObject.");

	//protected:
	//	x::vector<_Type*> reliants_;

	//	Handler();

	//public:
	//	
	//};

	/////////////////////////////////////////////////////////////////////////////////

	//template<class _Type>
	//inline Handler<_Type>::Handler():
	//	Handler<>(reliants_)
	//{
	//}

	///////////////////////////////////////////////////////////////////////////////

	template<class _Type>
	class Handler: public ThreadProcess
	{
		G_OBJECT;
		//static_assert(std::is_base_of<Reliant<_Type>, _Type>::value,
		//	"Handled _Type must derive from Reliant<_Type>");

	protected:
		x::vector<_Type*> reliants_;

		Handler();

	public:
		virtual void process() abstract override;
		virtual void clear() override;

		size_t getReliantsNumber() const;
		bool hasReliant(_Type* reliant) const;
		void addReliant(_Type* reliant);
		void detachReliant(_Type* reliant);

		virtual ~Handler();
	};

	///////////////////////////////////////////////////////////////////////////////

	template<class _Type>
	Handler<_Type>::Handler()
	{
	}

	template<class _Type>
	void Handler<_Type>::clear()
	{
		reliants_.delete_each();
		reliants_.clear();
	}

	template<class _Type>
	size_t Handler<_Type>::getReliantsNumber() const
	{
		return reliants_.size();
	}

	template<class _Type>
	bool Handler<_Type>::hasReliant(_Type * reliant) const
	{
		return (bool)reliants_.find(reliant);
	}

	template<class _Type>
	void Handler<_Type>::addReliant(_Type * reliant)
	{
		if (!reliant)
			return;

		auto relHandler = reliant->getHandler();
		if (!relHandler)
			static_cast<Reliant<_Type>*>(reliant)->register_(this);
		/*if (relHandler != this)
			return;*/
		if (!hasReliant(reliant))
			reliants_.push_back(reliant);
		/*if (reliant && reliant->getHandler() == this && !hasReliant(reliant))
			reliants_.push_back(reliant);*/
	}

	template<class _Type>
	void Handler<_Type>::detachReliant(_Type * reliant)
	{
		if (reliant)
			reliants_.remove(reliant);
	}

	template<class _Type>
	Handler<_Type>::~Handler()
	{
		clear();
	}

}
