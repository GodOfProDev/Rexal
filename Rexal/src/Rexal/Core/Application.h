#pragma once

#include "Rexal/Core/Base.h"

#include "Rexal/Core/Window.h"
#include "Rexal/Core/LayerStack.h"
#include "Rexal/Events/Event.h"
#include "Rexal/Events/ApplicationEvent.h"

#include "Rexal/Core/Timestep.h"

#include "Rexal/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Rexal {
	class Application
	{
	public:
		Application(const std::string& name = "Rexal Engine");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:	
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in Client
	Application* CreateApplication();
}