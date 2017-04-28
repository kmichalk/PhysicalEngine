#ifndef DRAWING_HANDLER_H
#define DRAWING_HANDLER_H

#include "PeriodicProcess.h"
#include "SFML\Graphics.hpp"
#include "RigidBody.h"
#include "ApplicationComponent.h"


namespace phs
{
	class PhysicalEngine;
}

namespace game
{
	class DrawingHandler: 
		virtual public ApplicationComponent, public PeriodicProcess
	{
		G_OBJECT;

		unsigned winW_;
		unsigned winH_;
		const char* winName_;


		void processWindowEvents_();
		void drawObjCount_();

	public:
		sf::RenderWindow* window_;
		x::vector<game::Element*> const& handledObjects_;


		double		static constexpr DEFAULT_DRAW_PERIOD	= 0.02;
		unsigned	static constexpr DEFAULT_WIN_W			= 800;
		unsigned	static constexpr DEFAULT_WIN_H			= 600;
		unsigned	static constexpr DEFAULT_FONT_SIZE		= 14;
		double		static constexpr DEFAULT_SCALE			= 100.0;
		double		static constexpr DEFAULT_FPS_FRAME_DUR	= 0.5;
		const char	static constexpr DEFAULT_WIN_NAME[]		= "Application";


		DrawingHandler(
			Application& parent,
			ProcessHandler* handler,
			x::vector<game::Element*>& handledObjects, 
			unsigned winW = DEFAULT_WIN_W,
			unsigned winH = DEFAULT_WIN_H,
			const char* winName = DEFAULT_WIN_NAME);

		DrawingHandler(
			game::Application& parent,
			ProcessHandler* handler,
			phs::PhysicalEngine& engine,
			unsigned winW = DEFAULT_WIN_W,
			unsigned winH = DEFAULT_WIN_H,
			const char* winName = DEFAULT_WIN_NAME);

		DrawingHandler(DrawingHandler const&);
		

		virtual void process() override;
		virtual void prepare() override;

		sf::RenderWindow const& getWindow() const; //TODO: maybe getMousePos method
		Point crdBegin() const;
		bool setFont(std::string fileName, unsigned fontSize);

		~DrawingHandler();
	};

}
#endif
//
//template<typename HandledType>
//class DrawingHandler: public TimedProcess
//{
//public:
//	sf::RenderWindow* window_;
//	x::vector<HandledType>& handledObjects_;
//	//double drawPeriod_;
//	//x::timer<std::chrono::microseconds> drawTimer_;
//
//	static constexpr double DEFAULT_DRAW_PERIOD = 0.02;
//	static constexpr unsigned DEFAULT_WIN_W = 800;
//	static constexpr unsigned DEFAULT_WIN_H = 600;
//	static constexpr unsigned DEFAULT_FONT_SIZE = 14;
//	static constexpr double DEFAULT_SCALE = 100.0;
//	static constexpr double DEFAULT_FPS_FRAME_DUR = 0.5;
//
//	DrawingHandler(x::vector<HandledType>& handledObjects):
//		TimedProcess{DEFAULT_DRAW_PERIOD},
//		handledObjects_{handledObjects},
//		window_{nullptr}
//	{
//	}
//
//	void process() override
//	{
//		window_ = new sf::RenderWindow{sf::VideoMode{800,600}, ""}; //TODO: parameters of window as members
//		TimedProcess::process();
//	}
//
//	void task() override
//	{
//		for (auto&& o : handledObjects_) {
//			x::deref(o).draw(*window_);
//		}
//		window_->display();
//		window_->clear();
//		processWindowEvents_();
//	}
//
//	void processWindowEvents_()
//	{
//		sf::Event event;
//		window_->pollEvent(event);
//		if (event.type == sf::Event::Closed) {
//			window_->close();
//		}
//	}
//
//	Point crdBegin() const
//	{
//		return Point{(basic_t)0,(basic_t)window_->getSize().y};
//	}
//
//	~DrawingHandler()
//	{
//		if (window_)
//			delete window_;
//	}
//};