#include "rxpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Rexal {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}