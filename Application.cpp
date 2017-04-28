#include "Application.h"
#include "xrnd.h"
#include "Emitter.h"
#include "disp.h"
#include "Mouse.h"
#include "KeyEvent.h"
#include "Function.h"
#include "ControllableGameObject.h"
#include "KeyboardController.h"

#define rnd x::random<double>

namespace game
{
	void Application::testEnvironment_1()
	{
		using namespace std;
		using namespace phs;

		x::always_seed<double>(true);

		try {
			game::Element::setEngine(engine_);
			//phs::RigidBody::setEngine(*engine_);
		}
		catch (x::error<>& e) {
			std::cout << e.message();
		}
		auto rect{new game::RectangleObject{{ 0.5, 0.5 }, {6,2.6} }};
		rect->physicalObject_->angularDynamics.angle = -0.7;
		rect->physicalObject_->angularDynamics.angularVelocity = 1.6;
		rect->physicalObject_->dynamics.velocity = {rnd(-3,3),rnd(-3,3)};
		//re->t.setStatic();
		rect->applyDefaults(Material::STEEL);

		auto rect2{new game::RectangleObject{{ 1, 2 }, {2.5,3} }};
		rect2->physicalObject_->angularDynamics.angle = PI / 4;
		//rect2.angularVel_ = 1;
		rect2->physicalObject_->dynamics.velocity = {7,2};
		rect2->applyDefaults(Material::STEEL);

		auto rect3{new game::RectangleObject{ { 1.2, 1.7 }, {4,4} }};
		//rect3->physicalObject_->angularDynamics.angularVelocity = 1;
		//rect3->physicalObject_->dynamics.velocity = {rnd(-3,3),rnd(-3,3)};
		rect3->applyDefaults(Material::STEEL);


		auto tempcir = new CircleObject{0.2,{4,3}};


		tempcir->applyDefaults(Material::STEEL);
		/*auto conCir = new ControllableGameObject{
			x::New<sf::CircleShape>{0.2f}, 
			x::New<phs::Circle>{(*(phs::Circle*)tempcir->physicalObject_)},
			CircleObject::OBJECT_TYPE_PROPERTIES_};*/
		auto conCir = new ControllableGameObject{(GameObject const&)(*tempcir)};
		conCir->controller_ = new KeyboardController{*this,conCir};
		conCir->controller_->run();
		conCir->getController()->setMovementKey(WKey::Up, MovementFlag::Type::UP);
		conCir->getController()->setMovementKey(WKey::Down, MovementFlag::Type::DOWN);
		conCir->getController()->setMovementKey(WKey::Left, MovementFlag::Type::LEFT);
		conCir->getController()->setMovementKey(WKey::Right, MovementFlag::Type::RIGHT);
		conCir->applyDefaults(Material::MASSIVE);
		conCir->physicalObject_->gravity = false;

		game::RectangleObject* l = new game::RectangleObject{{0.2,6},{-0.1,3},-0.0001};
		l->physicalObject_->setStatic();
		game::RectangleObject* r = new game::RectangleObject{{0.2,6},{8.1,3},0.0001};
		r->physicalObject_->setStatic();
		game::RectangleObject* u = new game::RectangleObject{{8,0.2},{4,-0.1}, 0.0001};
		u->physicalObject_->setStatic();
		game::RectangleObject* d = new game::RectangleObject{{8,0.2},{4,6.1}, -0.0001};
		d->physicalObject_->setStatic();

		disp "after 1\n";
		engine_->organizer_.add({l,r,u,d});
		engine_->organizer_.add(conCir);
		//engine_->organizer_.add(tempcir);
		//engine_->organizer_.add(rect3);


		auto mouse = new Mouse{};
		auto emitter = new Emitter{
			0.1,
			Emitter::SingleObject{
			//CircleObject{0.2,{}}},
			RectangleObject{{0.4,0.08}, { 0,0 }}},
			engine_->organizer_,
			Shooter(
				Value<Point>::createConst({4,3}),
				mouse->positionReference(),
				Value<basic_t>::createConst(8.0)),
			sf::CircleShape{10.0f},
			phs::Circle{engine_, nullptr, 0.1, Point{1.0,1.0}}};

		emitter->start();
		disp "after 2\n";
		engine_->organizer_.add(emitter);

		//system("pause");
		/*iter(i, 2, 15) {
		iter(j, 2, 11) {
		phs::Rectangle* rect = new phs::Rectangle{{0.5,0.5},{0.5*i,0.5*j},0.0001};
		rect->applyDefaults(Material::STONE);
		engine_->organizer_.add(rect);
		}
		}*/
		/*disp rect->sf::RectangleShape::getPosition().x;
		disp *rect;
		rect->setFillColor({255,255,255});
		engine_->organizer_.add(rect);
		engine_->organizer_.add(rect2);
		engine_->organizer_.add(rect3);*/

		//engine_->add(&circle);
		//engine_->add(&rect);*/


		drawer_->setFont("D:/VSProjects/PhisicalEngine/Debug/font.ttf", 14);

		//keyEventHandler_->setShortcut(WKey::P, engine_, &phs::PhysicalEngine::togglePause);
		//keyEventHandler_->setShortcut(WKey::A, emitter, &Emitter::toggleEnabled);
		/*auto lambda = [emitter] {emitter->setEnabled(false); };
		auto f = new Function<void()>{(decltype(lambda) && )(*new decltype(lambda){lambda})};
		f->execute();*/

		/*keyEventHandler_->addReliant(new KeyEvent{
			WKey::LMB,
			new Function<void()>{[emitter] {emitter->setEnabled(true); }},
			new Function<void()>{[emitter] {emitter->setEnabled(false); }}});*/


		
		//keyEventHandler_->setShortcut(WKey::G,
		//	&phs::PhysicalEngine::toggleGravity);
		//keyEventHandler_->setShortcut(WKey::R,
		//	&phs::PhysicalEngine::reset);
		///*setShortcut(WKey::End,
		//	&phs::Engine::end);*/

		//keyEventHandler_->setShortcut(WKey::F,
		//	new Function<void()>{[this]() {disp engine_->fps_, '\n', engine_->objects_.size(), "\n\n"; }});

		//keyEventHandler_->setShortcut(WKey::BackSpace,
		//	new Function<void()>{[this]() {engine_->organizer_.kill(engine_->objects_.end()-1); }});

		/*for (size_t i = 0; i<11; ++i) {
			keyEventHandler_->setShortcut(
				(WKey)(i+(int)WKey::Num0),
				x::FnCall<PhysicalEngine, void(Material::DefNum)>{engine_, &PhysicalEngine::spawnAtMouse, (Material::DefNum)i});
		}*/
		disp "shortcuts set\n";

		engine_->setTimeScale(1.0);
		//engine_->toggleGravity();
	}

	Application::Application()
		:
		engine_				{new phs::PhysicalEngine{*this, this}},
		keyEventHandler_	{new KeyEventHandler{*this}},
		drawer_				{new DrawingHandler{*this, this, *engine_}},
		get					{*this}
	{
		game::Element::setApplication(*this);
		addReliant(engine_);
		addReliant(keyEventHandler_);
		addReliant(drawer_);
	}

	void Application::prepare()
	{
		testEnvironment_1();
	}

	void Application::process()
	{
		while(running_) Sleep(10);
	}

	/*void Application::setShortcut(WKey key,	void(phs::PhysicalEngine::* fn)())
	{
		keyEventHandler_->addReliant(
			new KeyPressEvent{key,new Function<void()>{engine_,fn}});
	}

	void Application::setShortcut(WKey key,	void(Application::* fn)())
	{
		keyEventHandler_->addReliant(
			new KeyPressEvent{key,new Function<void()>{this,fn}});
	}

	void Application::setShortcut(WKey key, Procedure* fn)
	{
		keyEventHandler_->addReliant(
			new KeyPressEvent{key, fn});
	}*/

	void Application::addComponent(ApplicationComponent * component)
	{
		if (!components_.find(component))
			components_.push_back(component);
	}

	sf::Vector2i Application::GetInfoInterface::mousePosition() const
	{
		return sf::Mouse::getPosition(parent_.drawer_->getWindow());
	}
}