#include <Rexal.h>
#include <Rexal/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Rexal {

	class RexalEditor : public Application
	{
	public:
		RexalEditor()
			: Application("Rexal Editor")
		{
			PushLayer(new EditorLayer());
		}

		~RexalEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new RexalEditor();
	}
}