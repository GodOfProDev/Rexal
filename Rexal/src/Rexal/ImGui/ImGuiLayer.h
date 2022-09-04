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
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}