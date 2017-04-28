#pragma once

#include "Object.h"


namespace game
{
	//class Reliant;


	/*class Reliant
	{
		using HandlerType = Handler<>;

		Handler<>* handler_;

		void register_() const;

	public:
		Reliant(Handler<>* handler);

		Handler<>* getHandler() const;
	};
*/

	template<class _Type>
	class Reliant : virtual public Object
	{
		G_OBJECT;

		template<class>
		friend class Handler;

		Handler<_Type>* handler_;

		void register_();
		void register_(Handler<_Type>* handler);

	public:
		Reliant(Handler<_Type>* handler = nullptr);

		Handler<_Type>* getHandler() const;

		virtual ~Reliant();
	};
	
	///////////////////////////////////////////////////////////////////////////////	
	
	template<class _Type>
	void Reliant<_Type>::register_()
	{
		if (handler_)
			handler_->addReliant(dynamic_cast<_Type*>(x::rem_const(this)));
	}

	template<class _Type>
	inline void Reliant<_Type>::register_(Handler<_Type>* handler)
	{
		handler_ = handler;
	}

	template<class _Type>
	Reliant<_Type>::Reliant(Handler<_Type>* handler):
		handler_{handler}
	{
		register_();
	}

	template<class _Type>
	Handler<_Type>* Reliant<_Type>::getHandler() const
	{
		return handler_;
	}

	template<class _Type>
	Reliant<_Type>::~Reliant()
	{
	}
}
