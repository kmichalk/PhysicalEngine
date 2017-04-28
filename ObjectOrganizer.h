#ifndef OBJECT_ORGANIZER_H
#define OBJECT_ORGANIZER_H

#include "xvector.h"
#include "ObjectFactory.h"
#include "Clearable.h"

namespace game
{
	class ObjectOrganizer: public Clearable
	{
		using ObjIter = x::vector<Element*>::iterator;
		using CObjIter = x::vector<Element*>::const_iterator;

		x::vector<Element*> container_;
		size_t nDead_;

		void clearDead_();

		static constexpr size_t DEFAULT_CONTAINER_SIZE_ = 100;

	public: 
		ObjectOrganizer(size_t initialSize = DEFAULT_CONTAINER_SIZE_);
		
		void add(Element* obj);
		void add(std::initializer_list<Element*> objects);
		void kill(CObjIter obj);
		x::vector<Element*> const& accessObjects() const;

		virtual void clear() override;
	};

	///////////////////////////////////////////////////////////////////////////////

	inline x::vector<Element*> const & ObjectOrganizer::accessObjects() const
	{
		return container_;
	}
}
#endif //OBJECT_ORGANIZER_H
