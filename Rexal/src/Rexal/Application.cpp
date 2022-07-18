#include "rxpch.h"
#include "Application.h"

#include "Rexal/Events/ApplicationEvent.h"
#include "Rexal/Log.h"

namespace Rexal {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		RX_TRACE(e);

		while (true);
	}

	// To be defined in Client
	Application* CreateApplication();
}