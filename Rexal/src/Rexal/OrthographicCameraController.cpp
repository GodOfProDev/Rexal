#include "rxpch.h"
#include "OrthographicCameraController.h"

#include "Rexal/Input.h"
#include "Rexal/KeyCodes.h"

namespace Rexal {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep step)
	{
		if (Rexal::Input::IsKeyPressed(RX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraTranslateSpeed * step;
		else if (Rexal::Input::IsKeyPressed(RX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraTranslateSpeed * step;

		if (Rexal::Input::IsKeyPressed(RX_KEY_UP))
			m_CameraPosition.y += m_CameraTranslateSpeed * step;
		else if (Rexal::Input::IsKeyPressed(RX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraTranslateSpeed * step;

		if (m_Rotation)
		{
			if (Rexal::Input::IsKeyPressed(RX_KEY_A))
				m_CameraRotation += m_CameraRotationSpeed * step;
			if (Rexal::Input::IsKeyPressed(RX_KEY_D))
				m_CameraRotation -= m_CameraRotationSpeed * step;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispathcer(e);
		dispathcer.Dispatch<MouseScrolledEvent>(RX_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispathcer.Dispatch<WindowResizeEvent>(RX_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}