#pragma once

#include "Core.h"

#include "Window.h"
#include "Rexal/LayerStack.h"
#include "Rexal/Events/Event.h"
#include "Rexal/Events/ApplicationEvent.h"

#include "Rexal/Core/Timestep.h"

#include "Rexal/ImGui/ImGuiLayer.h"

namespace Rexal {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();
}