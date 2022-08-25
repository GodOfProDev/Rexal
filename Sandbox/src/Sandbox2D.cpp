#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 620.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA.reset(Rexal::VertexArray::Create());

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

	Rexal::BufferLayout squareLayout = {
			{ Rexal::ShaderDataType::Float3, "a_Position" }
	};

	Rexal::Ref<Rexal::VertexBuffer> squareVB;
	Rexal::Ref<Rexal::IndexBuffer> squareIB;

	squareVB.reset(Rexal::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareIB.reset(Rexal::IndexBuffer::Create(squareIndices, std::size(squareIndices)));

	squareVB->SetLayout(squareLayout);

	m_SquareVA->AddVertexBuffer(squareVB);
	m_SquareVA->SetIndexBuffer(squareIB);

	m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnUpdate(Rexal::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Rexal::RenderCommand::SetClearColor({ 0.5, 0.2, 1, 1 });
	Rexal::RenderCommand::Clear();

	Rexal::Renderer::BeginScene(m_CameraController.GetCamera());

	auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

	std::dynamic_pointer_cast<Rexal::OpenGLShader>(flatColorShader)->Bind();
	std::dynamic_pointer_cast<Rexal::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

	Rexal::Renderer::Submit(flatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Rexal::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Rexal::Event& e)
{
	m_CameraController.OnEvent(e);
}