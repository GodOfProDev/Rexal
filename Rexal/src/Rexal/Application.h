#pragma once

#include "Core.h"

#include "Window.h"
#include "Rexal/LayerStack.h"
#include "Rexal/Events/Event.h"
#include "Rexal/Events/ApplicationEvent.h"

#include "Rexal/ImGui/ImGuiLayer.h"

#include "Rexal/Renderer/Shader.h"
#include "Rexal/Renderer/Buffer.h"

namespace Rexal {
	class REXAL_API Application
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();
}