#ifndef APPLICATION_H
#define APPLICATION_H

#include "PhysicalEngine.h"
#include "ApplicationComponent.h"
#include "keyevent.h"
#include "MainThread.h"
#include "KeyEventHandler.h"


namespace game
{
	class Application: protected MainThread, virtual public ProcessHandler
	{
		G_OBJECT;

		class CommunicationInterface:
			public ApplicationComponent
		{
		public:
			using ApplicationComponent::ApplicationComponent;
		};

		class GetInfoInterface:
			public CommunicationInterface
		{
		public:
			sf::Vector2i mousePosition() const;

			using CommunicationInterface::CommunicationInterface;
		};

		phs::PhysicalEngine* engine_;
		KeyEventHandler* keyEventHandler_;
		DrawingHandler* drawer_;
		x::vector<ApplicationComponent*> components_;

		void testEnvironment_1();

	protected:
		/*using MainThread::clear;
		using MainThread::getHandler;
		using MainThread::join;
		using MainThread::stop;
		using MainThread::setEnabled;
		using MainThread::*/
		virtual void prepare() override;
		virtual void process() override;

	public:
		GetInfoInterface get;

		Application();

		using MainThread::run;

		/*void setShortcut(WKey key, void(phs::PhysicalEngine::*fn)());
		void setShortcut(WKey key, void(Application::*fn)());
		void setShortcut(WKey key, Procedure * fn);*/
		void addComponent(ApplicationComponent* component);
	};
}
#endif //APPLICATION_H
