#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Rexal/Events/ApplicationEvent.h"

#include "Window.h"

namespace Rexal {
	class REXAL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in Client
	Application* CreateApplication();
}