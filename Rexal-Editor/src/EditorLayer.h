#pragma once

#include "Rexal.h"

namespace Rexal {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		ShaderLibrary m_ShaderLibrary;
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_SquareVA;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Texture2D> m_CheckerboardTexture;

		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TextureStair;
		Ref<SubTexture2D> m_TextureTree;
		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	};

}