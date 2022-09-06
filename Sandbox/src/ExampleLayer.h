#pragma once

#include "Rexal.h"

class ExampleLayer : public Rexal::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Rexal::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Rexal::Event& e) override;
private:
	Rexal::ShaderLibrary m_ShaderLibrary;

	Rexal::Ref<Rexal::VertexArray> m_VertexArray;
	Rexal::Ref<Rexal::VertexArray> m_SquareVA;

	Rexal::Ref<Rexal::Texture2D> m_Texture;
	Rexal::Ref<Rexal::Texture2D> m_ChernoLogoTexture;

	Rexal::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};