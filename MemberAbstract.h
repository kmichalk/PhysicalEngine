#ifndef _MEMBER_ABSTRACT_H
#define _MEMBER_ABSTRACT_H

#include "GameObject.h"
#include "fn.h"
#include "xrnd.h"

//template<typename _Type>
//using MemberPtr = _Type(phs::RigidBody::*);
//
//template<typename _Type>
//class Member
//{
//	template<MemberPtr<_Type> _member>
//	class Abstract
//	{
//		void virtual apply(phs::RigidBody& object) const abstract;
//	};
//
//	template<MemberPtr<_Type> _member>
//	class Const:
//		public Abstract<_member>
//	{
//
//		MemberPtr<_Type> member_;
//
//	public:
//		Const(MemberPtr<_Type> member)
//			:
//			member_{member}
//		{
//		}
//
//		void virtual apply(phs::RigidBody& object) const override
//		{
//
//		}
//	};
//};
//
//template<class _Owner, typename _Type>
//class Member
//{
//	using MemberPtr = _Type(_Owner::*);
//
//	template<MemberPtr _member>
//	class Abstract
//	{
//	public:
//		void virtual apply(_Owner& object) const abstract;
//	};
//
//	template<MemberPtr _member>
//	class Const:
//		public Abstract<_member>
//	{
//		_Type value_;
//
//	public:
//		Const(_Type value)
//			:
//			value_{value}
//		{
//		}
//
//		Const(Const<_member> const& other)
//			:
//			value_{other.value_}
//		{
//		}
//
//		void virtual apply(_Owner& object) const override
//		{
//			object.*_member = value_;
//		}
//	};
//
//	template<MemberPtr _member>
//	class Copy:
//		public Abstract<_member>
//	{
//		_Owner const* trackedObject_;
//
//	public:
//		Copy(game::GameObject const* trackedObject)
//			:
//			trackedObject_{trackedObject}
//		{
//		}
//
//		Copy(Copy<_member> const& other)
//			:
//			trackedObject_{other.trackedObject_}
//		{
//		}
//
//		void virtual apply(_Owner& object) const override
//		{
//			object.*_member = trackedObject_->*_member;
//		}
//	};
//
//	template<MemberPtr _member>
//	class Relative:
//		public Copy<_member>
//	{
//		_Owner const* trackedObject_;
//		x::Fn<_Type(_Owner&, _Owner&)> func_;
//
//	public:
//		Relative(
//			game::GameObject const* trackedObject, 
//			x::Fn<_Type(_Owner&, _Owner&)> func)
//			:
//			trackedObject_	{trackedObject},
//			func_			{func}
//		{
//		}
//
//		Relative(Relative<_member> const& other)
//			:
//			trackedObject_	{other.trackedObject_},
//			func_			{other.func_}
//		{
//		}
//
//		void virtual apply(_Owner& object) const override
//		{
//			object.*_member = func_(*trackedObject_, object);
//		}
//	};
//};

template<typename _Type>
class Value
{
public:
	static x::Abstract<Value<_Type>> createConst(_Type value);
	static x::Abstract<Value<_Type>> createReference(_Type* ptr);
	template<typename _Owner>
	static x::Abstract<Value<_Type>> createMember(_Owner* owner, _Type(_Owner::*member));
	template<typename _Owner>
	static x::Abstract<Value<_Type>> createMember(_Owner* owner, _Type(_Owner::* member)() const);

	_Type virtual get() const abstract;
	void virtual set(_Type const&) abstract;
	virtual ~Value() {}
};

template<typename _Type>
using ValueAbstract = x::Abstract<Value<_Type>>;

template<typename _Type>
class Const:
	public Value<_Type>
{
	_Type value_;

public:
	Const(_Type value)
		:
		value_{value}
	{
	}

	Const(Const<_Type> const&) = default;
	Const(Const<_Type>&&) = default;

	_Type virtual get() const override
	{
		return value_;
	}

	void virtual set(_Type const& value) override
	{
		value_ = value;
	}
};

template<typename _Type>
class Reference:
	public Value<_Type>
{
	_Type* valuePtr_;

public:
	Reference(_Type* valuePtr)
		:
		valuePtr_{valuePtr}
	{
	}

	Reference(Reference<_Type> const&) = default;
	Reference(Reference<_Type>&&) = default;

	_Type virtual get() const override
	{
		return *valuePtr_;
	}

	void virtual set(_Type const& value) override
	{
		*valuePtr_ = value;
	}
};

template<typename...>
class Member;

template<typename _Type, typename _Owner>
class Member<_Type, _Owner>:
	public Value<_Type>
{
	_Owner* trackedObject_;
	_Type(_Owner::*member_);
public:
	Member(
		_Owner* trackedObject,
		_Type(_Owner::*member))
		:
		trackedObject_	{trackedObject},
		member_			{member}
	{
	}

	Member(Member<_Type,_Owner> const&) = default;
	Member(Member<_Type, _Owner> &&) = default;

	_Type virtual get() const override
	{
		return trackedObject_->*member_;
	}

	void virtual set(_Type const& value) override
	{
		trackedObject_->*member_ = value;
	}
};

template<typename _Type, typename _Owner>
class Member<_Type(), _Owner>:
	public Value<_Type>
{
	_Owner* trackedObject_;
	_Type(_Owner::*member_)() const;
public:
	Member(
		_Owner* trackedObject,
		_Type(_Owner::*member)() const)
		:
		trackedObject_{trackedObject},
		member_{member}
	{
	}

	Member(Member<_Type(), _Owner> const&) = default;
	Member(Member<_Type(), _Owner> &&) = default;

	_Type virtual get() const override
	{
		return (trackedObject_->*member_)();
	}

	void virtual set(_Type const& value) override
	{
		//trackedObject_->*member_ = value;
	}
};

template<typename _Type>
class Range
{
	x::Abstract<Value<_Type>> begin_;
	x::Abstract<Value<_Type>> end_;
public:
	Range(
		x::Abstract<Value<_Type>> const& begin, 
		x::Abstract<Value<_Type>> const& end)
		:
		begin_	{begin},
		end_	{end}
	{
	}

	_Type apply(_Type const& randomValue) const
	{
		return
			(((double)randomValue / (double)std::numeric_limits<_Type>::max())
				* (end_->get() - begin_->get()))
			+ begin_->get();
	}
};

//template<typename _Type>
//crd<_Type> Range<crd<_Type>>::apply(crd<_Type> const& randomValue) const
//{
//
//}

crd<double> Range<crd<double>>::apply(crd<double> const& randomValue) const
{
	crd<double> beginValue{begin_->get()};
	crd<double> endValue{end_->get()};

	return 
		crd<double>{
			((randomValue.x / std::numeric_limits<double>::max())
				* (endValue.x - beginValue.x))
			+ beginValue.x,
			((randomValue.y / std::numeric_limits<double>::max())
				* (endValue.y - beginValue.y))
			+ beginValue.y
	};
}

//template<typename _Type>
//class LinearRange:
//	public Range<_Type>
//{
//	_Type begin_;
//	_Type end_;
//public:
//	LinearRange(
//		_Type begin,
//		_Type end)
//		:
//		begin_	{begin},
//		end_	{end}
//	{
//	}
//
//	_Type virtual apply(_Type randomValue) const override
//	{
//		return 
//	}
//};

template<typename _Type>
class Random:
	public Value<_Type>
{
	Range<_Type> range_;
public:
	Random(
		x::Abstract<Value<_Type>> const& begin,
		x::Abstract<Value<_Type>> const& end)
		:
		range_{begin,end}
	{
	}

	Random(
		Random<_Type> const& other)
		:
		Value<_Type>(other),
		range_		{other.range_}
	{
	}

	Random(
		Random<_Type> && other)
		:
		Value<_Type>(other),
		range_		{std::move(other.range_)}
	{
	}

	_Type virtual get() const override
	{
		return range_.apply(x::random<_Type>())
	}

	void virtual set(_Type const& value) override
	{
		//trackedObject_->*member_ = value;
	}
};


template<typename _Type>
inline x::Abstract<Value<_Type>> Value<_Type>::createConst(_Type value)
{
	return x::New<Const<_Type>>{value};
}

template<typename _Type>
inline x::Abstract<Value<_Type>> Value<_Type>::createReference(_Type * ptr)
{
	return x::New<Reference<_Type>>{ptr};
}

template<typename _Type>
template<typename _Owner>
inline x::Abstract<Value<_Type>> Value<_Type>::createMember(_Owner * owner, _Type(_Owner::* member))
{
	return x::New<Member<_Type, _Owner>>{owner, member};
}

template<typename _Type>
template<typename _Owner>
inline x::Abstract<Value<_Type>> Value<_Type>::createMember(_Owner * owner, _Type(_Owner::* member)() const)
{
	return x::New<Member<_Type(), _Owner>>{owner, member};
}

#endif //_MEMBER_ABSTRACT_H