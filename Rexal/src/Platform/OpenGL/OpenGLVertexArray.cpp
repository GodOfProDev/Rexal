#include "rxpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Rexal {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Rexal::ShaderDataType::Float:    return GL_FLOAT;
			case Rexal::ShaderDataType::Float2:   return GL_FLOAT;
			case Rexal::ShaderDataType::Float3:   return GL_FLOAT;
			case Rexal::ShaderDataType::Float4:   return GL_FLOAT;
			case Rexal::ShaderDataType::Mat3:     return GL_FLOAT;
			case Rexal::ShaderDataType::Mat4:     return GL_FLOAT;
			case Rexal::ShaderDataType::Int:      return GL_INT;
			case Rexal::ShaderDataType::Int2:     return GL_INT;
			case Rexal::ShaderDataType::Int3:     return GL_INT;
			case Rexal::ShaderDataType::Int4:     return GL_INT;
			case Rexal::ShaderDataType::Bool:     return GL_BOOL;
		}

		RX_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		RX_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		RX_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		RX_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		RX_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		RX_PROFILE_FUNCTION();

		RX_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		RX_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}