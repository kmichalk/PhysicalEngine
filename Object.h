#pragma once

#include "Switchable.h"
#include "Copyable.h"
#include "more_type_traits.h"
#include "static_if.h"
#include "typeenum.h"
#include "xstring.h"
#include "id.h"


//#define DUMMY_MEMBER template<class = void> inline constexpr void __member__(){}
//
//#define THIS_CLASS x::owner_of_t<decltype(&__member__<>)>

class Object: public Switchable, public Copyable
{
	virtual void* cast_(x::num_t type);

public:
	x::id id;

	virtual Object* getThis();
	virtual Object const* getThis() const;
	virtual Copyable* copy() const override;
	virtual char const* getClassName() const;

	template<class _To>
	_To* cast();

	virtual ~Object();
};

///////////////////////////////////////////////////////////////////////////////

template<class _To>
inline _To * Object::cast()
{
	return reinterpret_cast<_To*>(cast_(typenum(_To)));
}


///////////////////////////////////////////////////////////////////////////////

#define G_OBJECT \
	public: \
		virtual inline Object* getThis() override { return this; }\
		virtual inline Object const* getThis() const override { return this; }\
		virtual char const* getClassName() const override {\
			return typeid(std::remove_pointer_t<decltype(this)>).name(); }\
		virtual inline Copyable* copy() const override { \
			__if_exists(opp) { return new this_type{*this}; }\
			return nullptr; }\
	private:\
		virtual inline void * cast_(x::num_t type) override { \
			return typenum(std::remove_pointer_t<decltype(this)>) == type ? this : nullptr; }
