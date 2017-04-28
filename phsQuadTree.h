#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "RigidBody.h"
#include "xvector.h"

namespace phs
{
	class CollisionSolver;

	class QuadTree
	{
		Point boundMin_;
		Point boundMax_;
		Point center_;
		QuadTree* children_[2][2];
		bool hasAny_;
		x::vector<RigidBody*> objects_;
		CollisionSolver* collider_;

		void processChildren_();
		void processChildren_(QuadTree& parent);
		void notifyChildren_(RigidBody* obj);
		QuadTree* createChild_(bool RL, bool UD) const;
		void displayChildren_(sf::RenderWindow& window) const;
		void delete_();

	public:
		static constexpr size_t DEFAULT_ELEMENTS_ALLOC_SIZE = 10;

		QuadTree() = delete;
		QuadTree(QuadTree const&) = delete;
		QuadTree(QuadTree&&) = delete;
		QuadTree(Point const& boundMin, Point const& boundMax, CollisionSolver* collider);

		void process(x::vector<game::Element*> const& objVec);
		void checkCollisions(RigidBody* obj);
		bool contains(RigidBody* obj) const;
		void split(unsigned times = 1);
		bool align(RigidBody* obj);
		bool insert(RigidBody* obj);
		void process();
		void process(QuadTree& parent);
		void notice(RigidBody* obj);
		void display(sf::RenderWindow& window) const;
		void clear();

		~QuadTree();
	};
}
#endif //QUAD_TREE_H