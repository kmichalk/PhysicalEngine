#include "ObjectOrganizer.h"

namespace game
{
	void ObjectOrganizer::clearDead_()
	{
		if (nDead_) {
			for (ObjIter obj{container_,container_.size()},
				endDeadObj{container_,container_.size() + nDead_};
				obj < endDeadObj;
				++obj) {
				if (*obj) {
					while (obj->nUsers()) {
					}
					delete *obj;
					*obj = nullptr;
					--nDead_;
				}
			}
		}
	}


	ObjectOrganizer::ObjectOrganizer(size_t initialSize):
		container_(initialSize),
		nDead_{0}
	{
	}

	void ObjectOrganizer::add(Element * obj)
	{
		clearDead_();
		container_.push_back(obj);
	}

	void ObjectOrganizer::add(std::initializer_list<Element*> objects)
	{
		clearDead_();
		container_.append(objects);
	}


	void ObjectOrganizer::kill(CObjIter obj)
	{
		obj->kill();
		container_.throw_back(obj.pos);
		//container_.pop_back();
		//container_.swap(obj.pos, container_.size());
	}

	void ObjectOrganizer::clear()
	{
		while (!container_.empty()) {
			foreach(obj, container_)
			{
				if (*obj) {
					if (obj->nUsers() == 0) {
						delete *obj;
						*obj = nullptr;
					}
					else continue;
				}
				container_.dump(obj.pos);
			}
		}
	}
}