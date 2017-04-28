#include "phsQuadTree.h"
#include "CollisionSolver.h"
#include "crd_cast.h"
#include "disp.h"

#include "GameObject.h"
#include "auto_cast.h"

#define _child_LD children_[0][0]
#define _child_LU children_[0][1]
#define _child_RD children_[1][0]
#define _child_RU children_[1][1]

#define FOR_ALL_CHILDREN(_member) \
if (_child_LD) _child_LD->_member;\
if (_child_LU) _child_LU->_member;\
if (_child_RD) _child_RD->_member;\
if (_child_RU) _child_RU->_member;

namespace phs
{
	QuadTree::QuadTree(Point const & boundMin, Point const & boundMax, CollisionSolver* collider):
		boundMin_{boundMin},
		boundMax_{boundMax},
		center_{mean(boundMin,boundMax)},
		children_{nullptr},
		hasAny_{false},
		objects_{DEFAULT_ELEMENTS_ALLOC_SIZE},
		collider_{collider}
	{
	}

	void QuadTree::process(x::vector<game::Element*> const & objVec)
	{ 
		for (auto obj{objVec.cbegin()}; obj; ++obj) {
			if (obj->properties.physical)
				insert(static_cast<game::GameObject*>(*obj)->physicalObject_);
		}
	}

	void QuadTree::checkCollisions(RigidBody * obj)
	{
		for (auto contained{objects_.begin()}; contained; ++contained) {
			//collider_.setObjects(obj, *contained);
			collider_->process(obj, *contained);
			//CollisionSolver{obj, *contained};
		}
	}

	bool QuadTree::contains(RigidBody * obj) const
	{
		return
			obj->dynamics.position.x - obj->volume.bound > boundMin_.x &&
			obj->dynamics.position.x + obj->volume.bound < boundMax_.x &&
			obj->dynamics.position.y - obj->volume.bound > boundMin_.y &&
			obj->dynamics.position.y + obj->volume.bound < boundMax_.y;
	}

	void QuadTree::split(unsigned times)
	{
		if (!times) return;
		booliter(RL, {
			booliter(UD, {
				if (!children_[RL][UD]) {
					children_[RL][UD] = createChild_(RL, UD);
				}
				if (times-1) children_[RL][UD]->split(times-1);
			})
		});
	}

	void QuadTree::processChildren_()
	{
		FOR_ALL_CHILDREN(process());
	}

	void QuadTree::processChildren_(QuadTree & parent)
	{
		FOR_ALL_CHILDREN(process(parent));
	}

	void phs::QuadTree::notifyChildren_(RigidBody * obj)
	{
		FOR_ALL_CHILDREN(notice(obj));
	}

	QuadTree * phs::QuadTree::createChild_(bool RL, bool UD) const
	{
		return new QuadTree{
			{RL ? center_.x : boundMin_.x, UD ? center_.y : boundMin_.y},
			{RL ? boundMax_.x : center_.x, UD ? boundMax_.y : center_.y},
			collider_
		};
	}

	bool QuadTree::align(RigidBody * obj)
	{
		if (contains(obj)) {
			bool RL = obj->dynamics.position.x > center_.x,
				UD = obj->dynamics.position.y > center_.y;
			QuadTree*& nextChild = children_[RL][UD];
			if (!nextChild) {
				nextChild = createChild_(RL, UD);					
			}
			if (!nextChild->align(obj)) {
				objects_.push_back(obj);
			}
			return true;
		}
		return false;
	}

	bool QuadTree::insert(RigidBody * obj)
	{
		if (!obj->static_) {
			int i = 0;
		}
		if (contains(obj)) {			
			bool RL = obj->dynamics.position.x > center_.x,
				UD = obj->dynamics.position.y > center_.y;
			QuadTree*& nextChild = children_[RL][UD];
			if (nextChild && nextChild->insert(obj)) {
				if (hasAny_) checkCollisions(obj);
				return hasAny_ = true;
			}
			notice(obj);
			objects_.push_back(obj);
			return hasAny_ = true;
		}
		return false;
	}

	/*bool QuadTree::insert(RigidBody * obj)
	{
		if (contains(obj)) {
			bool RL = obj->dynamics.position.x > center_.x,
				UD = obj->dynamics.position.y > center_.y;
			QuadTree*& nextChild = children_[RL][UD];
			if (nextChild && nextChild->insert(obj)) {
				return hasAny_ = true;
			}
			objects_.push_back(obj);
			return hasAny_ = true;
		}
		return false;
	}*/

	void QuadTree::process()
	{
		if (hasAny_) {
			for (auto obj1 = objects_.begin(); obj1; ++obj1) {
				for (auto obj2 = obj1+1u; obj2; ++obj2) {
					collider_->process(*obj1, *obj2);
					
					//CollisionSolver{*obj1, *obj2};
				}
			}
			processChildren_(*this);
		}
		else {
			processChildren_();
		}
	}

	void QuadTree::process(QuadTree& parent)
	{
		if (hasAny_) {
			for (auto obj1 = objects_.begin(); obj1; ++obj1) {
				for (auto obj2 = parent.objects_.begin(); obj2; ++obj2) {
					collider_->process(*obj1, *obj2);
					//CollisionSolver{*obj1, *obj2};
				}
				for (auto obj2 = obj1+1u; obj2; ++obj2) {
					collider_->process(*obj1, *obj2);
					//CollisionSolver{*obj1, *obj2};
				}
			}
			processChildren_(*this);
		}
		processChildren_(parent);
	}

	void phs::QuadTree::notice(RigidBody * obj)
	{
		if (hasAny_) {
			checkCollisions(obj);
			notifyChildren_(obj);
		}
	}

	void QuadTree::display(sf::RenderWindow& window) const
	{
		if (objects_) {
			sf::RectangleShape rect{{float(boundMax_.x-boundMin_.x), float(boundMax_.y-boundMin_.y)}};
			rect.setFillColor({0,0,0,0});
			rect.setOutlineColor(sf::Color::White);
			rect.setOutlineThickness(1);
			rect.setPosition(crd_cast<sf::Vector2f>(boundMin_));
			window.draw(rect);
			displayChildren_(window);
		}
	}

	void phs::QuadTree::displayChildren_(sf::RenderWindow& window) const
	{
		FOR_ALL_CHILDREN(display(window));
	}

	void phs::QuadTree::delete_()
	{
		delete this;
	}


	void QuadTree::clear()
	{
		objects_.clear();
		hasAny_ = false;
		FOR_ALL_CHILDREN(clear());
	}

	QuadTree::~QuadTree()
	{
		FOR_ALL_CHILDREN(delete_());
		delete collider_;
	}
}

#undef _child_LD
#undef _child_LU
#undef _child_RD
#undef _child_RU
#undef FOR_ALL_CHILDREN