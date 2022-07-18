#include "rxpch.h"
#include "Application.h"

#include "Rexal/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Rexal {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.5, 0.2, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	// To be defined in Client
	Application* CreateApplication();
}