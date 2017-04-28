#include "KeyEventHandler.h"


namespace game
{

	int KeyEventHandler::findPositionByKey_(WKey key) const
	{
		KeyEvent* e = nullptr;
		for (size_t r = 0, size = reliants_.size(); r < size; ++r) {
			e = (KeyEvent*)(reliants_[r]);
			if (e->getPrimaryKey() == key)
				return r;
		}
		return -1;
	}


	void KeyEventHandler::setShortcut(WKey key, Procedure * procedure)
	{
		addReliant(new KeyPressEvent{key, procedure});
	}

	void KeyEventHandler::setKeyEnabled(WKey key, bool value)
	{
		if (auto e = findByKey(key))
			e->setEnabled(value);
	}


	void KeyEventHandler::removeShortcut(WKey key)
	{
		reliants_.erase(findPositionByKey_(key));
	}


	KeyEvent * KeyEventHandler::findByKey(WKey key) const
	{
		Task* result = reliants_.find_by([key](Task* r) {
			return ((KeyEvent*)r)->getPrimaryKey() == key; 
		});
		return static_cast<KeyEvent*>(result);
		/*KeyEvent* e = nullptr;
		const_foreach(r, reliants_)
		{
			e = (KeyEvent*)(*r);
			if (e->getPrimaryKey() == key)
				return e;
		}
		return nullptr;*/
	}
}
