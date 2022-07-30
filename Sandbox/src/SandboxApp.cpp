#include <Rexal.h>

class ExampleLayer : public Rexal::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Rexal::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };

		Rexal::BufferLayout layout = {
			{ Rexal::ShaderDataType::Float3, "a_Position"},
			{ Rexal::ShaderDataType::Float4, "a_Color"}
		};
		
		std::shared_ptr<Rexal::VertexBuffer> vertexBuffer;
		std::shared_ptr<Rexal::IndexBuffer> indexBuffer;

		vertexBuffer.reset(Rexal::VertexBuffer::Create(vertices, sizeof(vertices)));
		indexBuffer.reset(Rexal::IndexBuffer::Create(indices, std::size(indices)));

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		#pragma region Shader
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
		#pragma endregion

		m_Shader.reset(new Rexal::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Rexal::Timestep ts) override
	{
		RX_INFO("Delta time: {0} ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Rexal::Input::IsKeyPressed(RX_KEY_LEFT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		else if (Rexal::Input::IsKeyPressed(RX_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		if (Rexal::Input::IsKeyPressed(RX_KEY_UP))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Rexal::Input::IsKeyPressed(RX_KEY_DOWN))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Rexal::Input::IsKeyPressed(RX_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		if (Rexal::Input::IsKeyPressed(RX_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		Rexal::RenderCommand::SetClearColor({ 0.5, 0.2, 1, 1 });
		Rexal::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Rexal::Renderer::BeginScene(m_Camera);

		Rexal::Renderer::Submit(m_Shader, m_VertexArray);

		Rexal::Renderer::EndScene();
	}

	void OnEvent(Rexal::Event& event) override
	{
	}

private:
	std::shared_ptr<Rexal::Shader> m_Shader;
	std::shared_ptr<Rexal::VertexArray> m_VertexArray;

	Rexal::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public Rexal::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Rexal::Application* Rexal::CreateApplication()
{
	return new Sandbox();
}