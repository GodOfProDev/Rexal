#include "rxpch.h"
#include "Rexal/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Rexal {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}