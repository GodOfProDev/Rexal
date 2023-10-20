#pragma once

#include "Rexal.h"
#include "Panels/SceneHierarchyPanel.h"

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
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		ShaderLibrary m_ShaderLibrary;
		OrthographicCameraController m_CameraController;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;

		Ref<VertexArray> m_SquareVA;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Texture2D> m_CheckerboardTexture;

		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TextureStair;
		Ref<SubTexture2D> m_TextureTree;
		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

		int m_GizmoType = -1;

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = {0, 0};

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}