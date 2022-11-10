#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles =
"000000000000000000000000"
"000001111111000000000000"
"000110001110110000000000"
"001100001110001100000000"
"011000011110000011000000"
"011000011110000011000000"
"011111111111111111000000"
"011000111111111111000000"
"011000011111111111000000"
"000110001111111111000000"
"000111111111111100000000"
"001111111111111111000000"
"011100000011111110000000"
"111100000011111110000000"
;
Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 620.0f)
{
}

void Sandbox2D::OnAttach()
{
	RX_PROFILE_FUNCTION();

	m_CheckerboardTexture = Rexal::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = Rexal::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_TextureStair = Rexal::SubTexture2D::CreateFromCoords(m_SpriteSheet, {7, 6}, {128, 128});
	m_TextureTree = Rexal::SubTexture2D::CreateFromCoords(m_SpriteSheet, {2, 1}, {128, 128}, {1, 2});

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	s_TextureMap['0'] = Rexal::SubTexture2D::CreateFromCoords(m_SpriteSheet, {11, 11}, {128, 128});
	s_TextureMap['1'] = Rexal::SubTexture2D::CreateFromCoords(m_SpriteSheet, {6, 11}, {128, 128});

	m_CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach()
{
	RX_PROFILE_FUNCTION();

}

void Sandbox2D::OnImGuiRender()
{
	RX_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Rexal::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();
}

void Sandbox2D::OnUpdate(Rexal::Timestep ts)
{
	RX_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	Rexal::Renderer2D::ResetStats();
	{
		RX_PROFILE_SCOPE("Renderer Prep");
		Rexal::RenderCommand::SetClearColor({ 0.25, 0.25, 0.25, 1 });
		Rexal::RenderCommand::Clear();
	}

	{
		RX_PROFILE_SCOPE("Renderer Draw");

		/*static float rotation = 0.0f;
		rotation += ts * 20.0f;

		Rexal::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Rexal::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Rexal::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Rexal::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Rexal::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Rexal::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);

		Rexal::Renderer2D::EndScene();*/

		Rexal::Renderer2D::BeginScene(m_CameraController.GetCamera());

		/*for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
				Rexal::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}*/

		for (uint32_t y = 0; y < m_MapHeight; y++)
		{
			for (uint32_t x = 0; x < m_MapWidth; x++)
			{
				char tileType = s_MapTiles[x + y * m_MapWidth];
				Rexal::Ref<Rexal::SubTexture2D> texture;
				if (s_TextureMap.find(tileType) != s_TextureMap.end())
					texture = s_TextureMap[tileType];
				else
					texture = m_TextureStair;

				Rexal::Renderer2D::DrawQuad({x - m_MapWidth / 2.0f,m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
			}
		}

		//Rexal::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TextureStair);
		//Rexal::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 1.0f, 2.0f }, m_TextureTree);

		Rexal::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnEvent(Rexal::Event& e)
{
	m_CameraController.OnEvent(e);
}