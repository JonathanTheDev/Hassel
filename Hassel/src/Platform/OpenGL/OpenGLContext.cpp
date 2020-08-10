#include "hslpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hassel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HSL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HSL_CORE_ASSERT(status, "Failed to intialized Glad!");

		HSL_CORE_INFO("OpenGL Info:");
		HSL_CORE_INFO(" - Vendor:	{0}", glGetString(GL_VENDOR));
		HSL_CORE_INFO(" - Renderer:	{0}", glGetString(GL_RENDERER));
		HSL_CORE_INFO(" - Version:	{0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}