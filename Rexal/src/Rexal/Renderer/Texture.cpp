#include "rxpch.h"
#include "Rexal/Renderer/Texture.h"

#include "Rexal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Rexal {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: RX_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}

		RX_CORE_ASSERT(false, "Unkown RendererAPI");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: RX_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}

		RX_CORE_ASSERT(false, "Unkown RendererAPI");
		return nullptr;
	}

}