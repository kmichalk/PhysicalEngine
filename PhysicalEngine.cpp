#include "PhysicalEngine.h"

#include "xrnd.h"
#include <string>
#include "DefaultCollisionSolver.h"
#include "crd_cast.h"
#include "phsQuadTree.h"
#include "Application.h"

#define rnd x::random<double>

namespace phs
{
	/*void Engine::checkCollisions_(ObjIter obj)
	{
		for (auto o{obj+1}; o; ++o) {
			phs::DefaultCollisionSolver{*obj, *o};
		}
	}*/

	void PhysicalEngine::processObjects_()
	{
		quadTreeProcessor_.clear();
		quadTreeProcessor_.process(organizer_.accessObjects());
		moveObjects_();
	}

	void PhysicalEngine::moveObjects_()
	{
		const_foreach(obj, organizer_.accessObjects()) {
			obj->process();
			if (obj->isAlive()) {
				if (obj->properties.physical)
					static_cast<game::GameObject*>(*obj)->physicalObject_->move(x::cutg(curFrame_*timeScale_, minFrameTime_));
			}
			else {
				organizer_.kill(obj);
			}
		}
	}

	void PhysicalEngine::countCurFrame_()
	{
		//curFrame_ = x::cutg(computeTimer_.measure(), minFrameTime_);
		curFrame_ = computeTimer_.measure();
	}

	void PhysicalEngine::countFPS_()
	{
		fps_ = 1.0/curFrame_;
	}

	PhysicalEngine::PhysicalEngine(
		game::Application& parent,
		game::ProcessHandler* handler,
		Size visibleSize, 
		double scale, 
		Vector Fg)
		:
		ApplicationComponent(parent),
		ThreadProcess		(handler),
		timeScale_			{DEFAULT_TIME_SCALE},
		minFrameTime_		{DEFAULT_MIN_FRAME_TIME},
		curFrame_			{0},
		visibleSize_		{visibleSize},
		scale_				{scale,-scale},
		crdBegin_			{0, visibleSize.y},
		paused_				{false},
		computeTimer_		{},
		fps_				{0},		
		//objects_			{DEFAULT_OBJ_CONTAINER_SIZE},
		gravityAcc_			{Fg},
		//collider_			{new DefaultCollisionSolver},
		quadTreeProcessor_	{{-8,-6},{16,12}, new DefaultCollisionSolver},
		organizer_			{DEFAULT_OBJ_CONTAINER_SIZE},
		factory_			{}
	{
		//crdBegin_ = drawer_.crdBegin();
		//objects_.fill(nullptr);
		quadTreeProcessor_.split(DEFAULT_QUAD_TREE_SPLIT);
		//fpsText_.setPosition(25, 15);
		//objCountText_.setPosition(25, 30);
	}


	PhysicalEngine::PhysicalEngine(PhysicalEngine const & other):
		ApplicationComponent(other.parent_),
		ThreadProcess(static_cast<game::ProcessHandler*>(other.getHandler())),
		timeScale_{DEFAULT_TIME_SCALE},
		minFrameTime_{DEFAULT_MIN_FRAME_TIME},
		curFrame_{0},
		visibleSize_{other.visibleSize_},
		scale_{other.scale_},
		crdBegin_{other.crdBegin_},
		paused_{false},
		computeTimer_{},
		fps_{0},
		//objects_{DEFAULT_OBJ_CONTAINER_SIZE},
		gravityAcc_{other.gravityAcc_},
		//collider_{other.collider_},
		quadTreeProcessor_{{-8,-6},{16,12}, new DefaultCollisionSolver},
		organizer_{DEFAULT_OBJ_CONTAINER_SIZE},
		factory_{}
	{
		quadTreeProcessor_.split(DEFAULT_QUAD_TREE_SPLIT);
	}



	Point PhysicalEngine::getScale() const
	{
		return scale_;
	}

	basic_t PhysicalEngine::absScale() const
	{
		return scale_.x;
	}

	Point PhysicalEngine::crdBegin() const
	{
		return crdBegin_;
	}

	Vector PhysicalEngine::gravityAcc() const
	{
		return gravityAcc_;
	}

	void PhysicalEngine::add(game::GameObject * object)
	{
		//try {
			//object->physicalObject_->setEngine(this);
			organizer_.add(object);
		//}
		//catch (x::error<phs::RigidBody> err) {
		//	std::cout<<err;
		//}
	}

	void PhysicalEngine::togglePause()
	{
		//this;		
		//std::cout<< this<< " toggle pause\n";
		paused_ = !paused_;
	}

	void PhysicalEngine::toggleGravity()
	{
		static Vector prevGravityAcc = {0,0};
		std::swap(gravityAcc_, prevGravityAcc);
		//gravityAcc_ = {0,0};
	}

	void PhysicalEngine::setTimeScale(double timeScale)
	{
		if (timeScale>0)
			timeScale_ = timeScale;
	}

	void PhysicalEngine::reset()
	{
		//clear();
		game::CircleObject* c;  game::RectangleObject* r;
		repeat(1000) {
			if (x::decide(0)) {
				c = new game::CircleObject{
					rnd(0.02, 0.03),
					{rnd(0.5,7.5),
					rnd(0.5,5.5)}};
				//c->dynamics.velocity = {rnd(-5,5),rnd(-5,5)};
				c->applyDefaults(Material::STONE);
				organizer_.add(c);
			}
			else {
				r = new  game::RectangleObject{
					{rnd(0.02, 0.04),rnd(0.02,0.04)},
					{rnd(0.5,7.5),
					rnd(0.5,5.5)}};
				//r->dynamics.velocity = {rnd(-1,1),rnd(-1,1)};
				//r->angularVel_ = rnd(-2, 2);
				r->applyDefaults(Material::STONE);
				organizer_.add(r);
			}
			//add(new Circle(rnd(1, 5), rnd(0.1, 0.2), Material::steel, sf::Color::White, {rnd(1,7), rnd(1,5)}, {rnd(-3,3),rnd(-3,3)}, {0,0}));
		}
	}

	/*void Engine::add(phs::RigidBody * obj)
	{
		deleteDeadObjects_();
		objects_.push_back(obj);
	}

	void Engine::add(std::initializer_list<phs::RigidBody*> objects)
	{
		deleteDeadObjects_();
		objects_.append(objects);
	}*/

	void PhysicalEngine::spawnAtMouse(Material::DefNum num)
	{
		game::GameObject* obj =
			(x::decide() ?
				(game::GameObject*) new game::RectangleObject{
					{rnd(0.5,1),rnd(0.5,1)},
					realPos(parent_.get.mousePosition()),
					rnd(-0.01,0.01)} :
				(game::GameObject*) new game::CircleObject{
					rnd(0.2,0.4),
					realPos(parent_.get.mousePosition()),
					rnd(0,PI*2)});
		obj->applyDefaults(num);
		organizer_.add(obj);
	}

	void PhysicalEngine::clear()
	{
		organizer_.clear();
		//objects_.delete_each();
		//objects_.clear();
	}

	
	void PhysicalEngine::run()
	{
		computeTimer_.tic();
		ThreadProcess::run();
		/*while (running_) {
			countCurFrame_();
			countFPS_();
			if (!paused_) {
				processObjects_();
			}
		}*/
		/*running_ = true;
		computeTimer_.tic();

		while (running_) {
			countCurFrame_();
			countFPS_();
			if (!paused_) {
				processObjects_();
			}
		}*/
	}

	void PhysicalEngine::process()
	{
		countCurFrame_();
		//std::cout<< fps_;
		countFPS_();
		if (!paused_) {
			processObjects_();
		}
	}

	PhysicalEngine::~PhysicalEngine()
	{
		clear();
	}

}