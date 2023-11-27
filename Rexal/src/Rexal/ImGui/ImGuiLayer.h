#pragma once

#include "Rexal/Core/Layer.h"

#include "Rexal/Events/MouseEvent.h"
#include "Rexal/Events/ApplicationEvent.h"
#include "Rexal/Events/KeyEvent.h"

namespace Rexal {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
	};
}