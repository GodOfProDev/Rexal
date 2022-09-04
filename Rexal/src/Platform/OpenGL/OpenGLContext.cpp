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
		RX_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RX_CORE_ASSERT(status, "Failed to initialize Glad");

		RX_CORE_INFO("OpenGL Info:");

		RX_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		RX_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		RX_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));

		RX_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Rexal requires at least OpenGL version 4.5!");
	}
	void OpenGLContext::SwapBuffers()
	{
		RX_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}