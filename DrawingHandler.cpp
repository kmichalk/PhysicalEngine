#include "DrawingHandler.h"
#include "PhysicalEngine.h"
#include "phsQuadTree.h"
#include "ProcessHandler.h"

namespace game
{
	DrawingHandler::DrawingHandler(
		game::Application& parent,
		ProcessHandler* handler,
		x::vector<game::Element*>& handledObjects,
		unsigned winW,
		unsigned winH,
		const char* winName)
		:
		ApplicationComponent(parent),
		PeriodicProcess(handler, DEFAULT_DRAW_PERIOD),
		handledObjects_{handledObjects},
		window_{nullptr},
		winW_{winW},
		winH_{winH},
		winName_{winName}
	{
	}

	DrawingHandler::DrawingHandler(
		game::Application& parent,
		ProcessHandler* handler,
		phs::PhysicalEngine & engine, 
		unsigned winW, 
		unsigned winH, 
		const char * winName)
		:
		ApplicationComponent{parent},
		PeriodicProcess(handler, DEFAULT_DRAW_PERIOD),
		handledObjects_{engine.organizer_.accessObjects()},
		window_{nullptr},
		winW_{winW},
		winH_{winH},
		winName_{winName}
	{
	}

	DrawingHandler::DrawingHandler(DrawingHandler const & other):
		ApplicationComponent{other.parent_},
		PeriodicProcess(static_cast<ProcessHandler*>(other.getHandler()), DEFAULT_DRAW_PERIOD),
		handledObjects_{other.handledObjects_},
		window_{nullptr},
		winW_{other.winW_},
		winH_{other.winH_},
		winName_{other.winName_}
	{
	}

	bool DrawingHandler::setFont(
		std::string fileName, 
		unsigned fontSize)
	{
		return true;
		//fontSize_ = fontSize;
		//return font_.loadFromFile(fileName);
	}

	void DrawingHandler::drawObjCount_()
	{
		//objCountText.setString(std::to_string(objects_.size()));
		//window_.draw(objCountText_);
	}

	void DrawingHandler::process()
	{
		const_foreach (o, handledObjects_){
			if (o->isAlive()) {
				++o->nUsers;
				if (o->isVisible()) {
					static_cast<game::Drawable const*>(*o)->draw(*window_);
					//window_->draw(*static_cast<game::GameObject*>(o));
				}
				--o->nUsers;
			}
		}
		window_->display();
		window_->clear();
		processWindowEvents_();
	}

	void DrawingHandler::prepare()
	{
		window_ = new sf::RenderWindow{sf::VideoMode{winW_, winH_}, winName_};
	}

	sf::RenderWindow const & DrawingHandler::getWindow() const
	{
		if (window_)
			return *window_;
		else
			throw x::error<DrawingHandler>{0, "Window not initialized."};
	}

	void DrawingHandler::processWindowEvents_()
	{
		sf::Event event;
		window_->pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window_->close();
		}
	}

	Point DrawingHandler::crdBegin() const
	{
		return Point{(basic_t)0,(basic_t)window_->getSize().y};
	}

	DrawingHandler::~DrawingHandler()
	{
		if (window_)
			delete window_;
	}
}