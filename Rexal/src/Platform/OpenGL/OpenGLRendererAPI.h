#pragma once

#include "Rexal/Renderer/RendererAPI.h"

namespace Rexal {

	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};

}