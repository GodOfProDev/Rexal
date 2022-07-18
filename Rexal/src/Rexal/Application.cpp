#include "Application.h"

namespace Rexal {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true);
	}

	// To be defined in Client
	Application* CreateApplication();
}