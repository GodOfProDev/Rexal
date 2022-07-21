#include "rxpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Rexal {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		RX_CORE_ASSERT(windowHandle, "Window handle is null");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RX_CORE_ASSERT(status, "Failed to initialize Glad");

		RX_CORE_INFO("OpenGL Info:");

		RX_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		RX_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		RX_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}