#pragma once

#include "Rexal.h"

class Sandbox2D : public Rexal::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Rexal::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Rexal::Event& e) override;
private:
	Rexal::ShaderLibrary m_ShaderLibrary;
	Rexal::OrthographicCameraController m_CameraController;

	Rexal::Ref<Rexal::VertexArray> m_SquareVA;
	Rexal::Ref<Rexal::Texture2D> m_CheckerboardTexture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f};
};

