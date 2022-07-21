#include "rxpch.h"
#include "Application.h"

#include <glad/glad.h>

namespace Rexal {

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Rexal::ShaderDataType::Float:    return GL_FLOAT;
			case Rexal::ShaderDataType::Float2:   return GL_FLOAT;
			case Rexal::ShaderDataType::Float3:   return GL_FLOAT;
			case Rexal::ShaderDataType::Float4:   return GL_FLOAT;
			case Rexal::ShaderDataType::Mat3:     return GL_FLOAT;
			case Rexal::ShaderDataType::Mat4:     return GL_FLOAT;
			case Rexal::ShaderDataType::Int:      return GL_INT;
			case Rexal::ShaderDataType::Int2:     return GL_INT;
			case Rexal::ShaderDataType::Int3:     return GL_INT;
			case Rexal::ShaderDataType::Int4:     return GL_INT;
			case Rexal::ShaderDataType::Bool:     return GL_BOOL;
		}

		RX_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	Application::Application()
	{
		RX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(RX_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);	

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"}
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_IndexBuffer.reset(IndexBuffer::Create(indices, std::size(indices)));

		m_VertexBuffer->SetLayout(layout);

		uint32_t index = 0;
		for (const auto& element : layout)
		{	
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void *) element.Offset);
			index++;
		}

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(RX_BIND_EVENT_FN(Application::OnWindowClose));

		//RX_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}


	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.5, 0.2, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	// To be defined in Client
	Application* CreateApplication();
}