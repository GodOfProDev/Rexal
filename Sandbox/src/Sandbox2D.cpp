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

	Rexal::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Rexal::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f , 1.0f });
	Rexal::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 1.0f, 0.0f, 0.0f , 1.0f });

	Rexal::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Rexal::Event& e)
{
	m_CameraController.OnEvent(e);
}