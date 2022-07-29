#pragma once

#include "Core.h"

#include "Window.h"
#include "Rexal/LayerStack.h"
#include "Rexal/Events/Event.h"
#include "Rexal/Events/ApplicationEvent.h"

#include "Rexal/ImGui/ImGuiLayer.h"

#include "Rexal/Renderer/Shader.h"
#include "Rexal/Renderer/Buffer.h"
#include "Rexal/Renderer/VertexArray.h"

#include "Rexal/Renderer/OrthographicCamera.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();
}