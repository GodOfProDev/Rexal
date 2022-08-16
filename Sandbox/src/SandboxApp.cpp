#include <Rexal.h>

#include <imgui/imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Rexal::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Rexal::VertexArray::Create());
		m_SquareVA.reset(Rexal::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f
		};
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		Rexal::BufferLayout layout = {
			{ Rexal::ShaderDataType::Float3, "a_Position"},
			{ Rexal::ShaderDataType::Float4, "a_Color"}
		};
		Rexal::BufferLayout squareLayout = {
			{ Rexal::ShaderDataType::Float3, "a_Position" },
			{ Rexal::ShaderDataType::Float2, "a_TexCoord" }
		};
		
		Rexal::Ref<Rexal::VertexBuffer> vertexBuffer;
		Rexal::Ref<Rexal::IndexBuffer> indexBuffer;
		Rexal::Ref<Rexal::VertexBuffer> squareVB;
		Rexal::Ref<Rexal::IndexBuffer> squareIB;

		vertexBuffer.reset(Rexal::VertexBuffer::Create(vertices, sizeof(vertices)));
		indexBuffer.reset(Rexal::IndexBuffer::Create(indices, std::size(indices)));
		squareVB.reset(Rexal::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareIB.reset(Rexal::IndexBuffer::Create(squareIndices, std::size(squareIndices)));

		vertexBuffer->SetLayout(layout);
		squareVB->SetLayout(squareLayout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->SetIndexBuffer(squareIB);

		#pragma region Shader
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		#pragma region FlatColorShader
		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";
		#pragma endregion

		#pragma region TextureShader
		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";
		#pragma endregion

		m_Shader.reset(Rexal::Shader::Create(vertexSrc, fragmentSrc));
		m_FlatColorShader.reset(Rexal::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
		m_TextureShader.reset(Rexal::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Rexal::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Rexal::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Rexal::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Rexal::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Rexal::Timestep ts) override
	{
		RX_INFO("Delta time: {0} ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Rexal::Input::IsKeyPressed(RX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Rexal::Input::IsKeyPressed(RX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Rexal::Input::IsKeyPressed(RX_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Rexal::Input::IsKeyPressed(RX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Rexal::Input::IsKeyPressed(RX_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Rexal::Input::IsKeyPressed(RX_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Rexal::RenderCommand::SetClearColor({ 0.5, 0.2, 1, 1 });
		Rexal::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Rexal::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Rexal::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Rexal::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Rexal::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Rexal::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Rexal::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		// Triangle
		//Rexal::Renderer::Submit(m_Shader, m_VertexArray);

		Rexal::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Rexal::Event& event) override
	{
	}

private:
	Rexal::Ref<Rexal::Shader> m_Shader;
	Rexal::Ref<Rexal::VertexArray> m_VertexArray;

	Rexal::Ref<Rexal::Shader> m_FlatColorShader, m_TextureShader;
	Rexal::Ref<Rexal::VertexArray> m_SquareVA;

	Rexal::Ref<Rexal::Texture2D> m_Texture;
	Rexal::Ref<Rexal::Texture2D> m_ChernoLogoTexture;

	Rexal::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
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