#include "Rexal.h"
#include "ExampleLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), m_CameraController(1280.0f / 620.0f)
{
	m_VertexArray = Rexal::VertexArray::Create();
	m_SquareVA = Rexal::VertexArray::Create();

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

	Rexal::Ref<Rexal::VertexBuffer> vertexBuffer = Rexal::VertexBuffer::Create(vertices, sizeof(vertices));
	Rexal::Ref<Rexal::IndexBuffer>  indexBuffer = Rexal::IndexBuffer::Create(indices, std::size(indices));
	Rexal::Ref<Rexal::VertexBuffer> squareVB = Rexal::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	Rexal::Ref<Rexal::IndexBuffer>  squareIB = Rexal::IndexBuffer::Create(squareIndices, std::size(squareIndices));

	vertexBuffer->SetLayout(layout);
	squareVB->SetLayout(squareLayout);

	m_VertexArray->AddVertexBuffer(vertexBuffer);
	m_VertexArray->SetIndexBuffer(indexBuffer);
	m_SquareVA->AddVertexBuffer(squareVB);
	m_SquareVA->SetIndexBuffer(squareIB);

	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
	m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");

	m_Texture = Rexal::Texture2D::Create("assets/textures/Checkerboard.png");
	m_ChernoLogoTexture = Rexal::Texture2D::Create("assets/textures/ChernoLogo.png");

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Rexal::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Rexal::RenderCommand::SetClearColor({ 0.5, 0.2, 1, 1 });
	Rexal::RenderCommand::Clear();

	Rexal::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

	flatColorShader->Bind();
	flatColorShader->SetFloat3("u_Color", m_SquareColor);


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

	Rexal::Renderer::EndScene();
}
void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
void ExampleLayer::OnEvent(Rexal::Event& e)
{
	m_CameraController.OnEvent(e);
}