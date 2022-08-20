#include <Rexal.h>

#include <imgui/imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Rexal/Renderer/Shader.h"

class ExampleLayer : public Rexal::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280 / 620)
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

		m_Shader = Rexal::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");

		m_Texture = Rexal::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Rexal::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Rexal::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Rexal::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Rexal::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Rexal::RenderCommand::SetClearColor({ 0.5, 0.2, 1, 1 });
		Rexal::RenderCommand::Clear();

		Rexal::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

		std::dynamic_pointer_cast<Rexal::OpenGLShader>(flatColorShader)->Bind();
		std::dynamic_pointer_cast<Rexal::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Rexal::Renderer::Submit(flatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Rexal::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Rexal::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
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

	void OnEvent(Rexal::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Rexal::ShaderLibrary m_ShaderLibrary;
	Rexal::Ref<Rexal::Shader> m_Shader;

	Rexal::Ref<Rexal::VertexArray> m_VertexArray;
	Rexal::Ref<Rexal::VertexArray> m_SquareVA;

	Rexal::Ref<Rexal::Texture2D> m_Texture;
	Rexal::Ref<Rexal::Texture2D> m_ChernoLogoTexture;

	Rexal::OrthographicCameraController m_CameraController;

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