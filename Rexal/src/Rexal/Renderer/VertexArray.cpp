#include "rxpch.h"
#include "Rexal/Renderer/VertexArray.h"

#include "Rexal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Rexal {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: RX_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		RX_CORE_ASSERT(false, "Unkown RendererAPI");
		return nullptr;
	}
}