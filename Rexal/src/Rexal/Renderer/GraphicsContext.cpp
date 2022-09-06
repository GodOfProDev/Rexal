#include "rxpch.h"
#include "Rexal/Renderer/GraphicsContext.h"

#include "Rexal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Rexal {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    RX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		RX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}