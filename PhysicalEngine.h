#pragma once
#include <atomic>
#include "xvector.h"
#include "Timer.h"
#include "signals.h"
#include "DrawingHandler.h"
#include "phsQuadTree.h"
#include "ObjectOrganizer.h"
#include "GameObject.h"
#include "ApplicationComponent.h"
#include "ThreadProcess.h"

namespace phs
{
	class PhysicalEngine:
		public game::ApplicationComponent, public game::ThreadProcess
	{
		G_OBJECT;
	public:
		friend class DrawingHandler;
		//using ObjIter = x::vector<game::GameObject*>::iterator;

		double timeScale_;
		double minFrameTime_;
		long double curFrame_;
		Size visibleSize_;
		Point scale_;
		Point crdBegin_;

		volatile bool paused_;
		Timer computeTimer_;
		double fps_;
		
		//x::vector<game::Element*> objects_;

		Vector gravityAcc_;
		//CollisionSolver* collider_;
		QuadTree quadTreeProcessor_;
		game::ObjectOrganizer organizer_;
		game::ObjectFactory factory_;

		//void checkCollisions_(ObjIter obj);
		void processObjects_();
		void moveObjects_();
		void countCurFrame_();
		void countFPS_();

	public:		
		basic_t		static constexpr DEFAULT_G					= -9.80665;
		double		static constexpr DEFAULT_TIME_SCALE			= 1.0;
		double		static constexpr DEFAULT_MIN_FRAME_TIME		= 0.02;
		size_t		static constexpr DEFAULT_OBJ_CONTAINER_SIZE = 4000;
		unsigned	static constexpr DEFAULT_QUAD_TREE_SPLIT	= 3;
		Size		static constexpr DEFAULT_VISIBLE_SIZE		= {8.0,6.0};

		PhysicalEngine(
			game::Application& parent,
			game::ProcessHandler* handler,
			Size visibleSize	= DEFAULT_VISIBLE_SIZE,
			basic_t scale		= game::DrawingHandler::DEFAULT_SCALE,
			Vector Fg			= {0,DEFAULT_G});

		PhysicalEngine(PhysicalEngine const& other);

		void virtual run() override;
		void virtual process() override;

		long double curFrame() const;
		Point getScale() const;
		basic_t absScale() const;
		template<typename _Type = float> sf::Vector2<_Type> dispPos(Point const& P) const;
		template<typename _Type> Point realPos(sf::Vector2<_Type> const& P) const;
		//Point realPos(sf::Vector2f const& P) const;
		Point crdBegin() const;
		Vector gravityAcc() const;

		void add(game::GameObject* object);
		void togglePause();
		void toggleGravity();
		void setTimeScale(double timeScale);
		void reset();
		void spawnAtMouse(Material::DefNum num);
		void clear();

		~PhysicalEngine();
	};


	inline long double PhysicalEngine::curFrame() const
	{
		return curFrame_;
	}

	//sf::Vector2f Engine::dispPos(Point const & P) const
	//{
	//	return sf::Vector2f{
	//		float((P.x-crdBegin_.x)*scale_.x),
	//		float((P.y-crdBegin_.y)*scale_.y)};
	//}

	//Point Engine::realPos(sf::Vector2i const & P) const
	//{
	//	return Point{
	//		basic_t(P.x)/scale_.x+crdBegin_.x,
	//		basic_t(P.y)/scale_.y+crdBegin_.y};
	//}

	template<typename _Type>
	inline sf::Vector2<_Type> PhysicalEngine::dispPos(Point const & P) const
	{
		return sf::Vector2f{
			float((P.x-crdBegin_.x)*scale_.x),
			float((P.y-crdBegin_.y)*scale_.y)};
	}

	template<typename _Type>
	inline Point PhysicalEngine::realPos(sf::Vector2<_Type> const & P) const
	{
		return Point{
			basic_t(P.x)/scale_.x+crdBegin_.x,
			basic_t(P.y)/scale_.y+crdBegin_.y};
	}

	//Point Engine::realPos(sf::Vector2f const & P) const
	//{
	//	return Point{
	//		basic_t(P.x)/scale_.x+crdBegin_.x,
	//		basic_t(P.y)/scale_.y+crdBegin_.y};
	//}
}