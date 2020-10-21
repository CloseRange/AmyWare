#include "awpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace AmyWare {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) {
		this->windowHandle = windowHandle;
		AW_CORE_ASSERT(windowHandle,"GLFW Window has not yet been defined!");
	}
	void OpenGLContext::Init() {
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AW_CORE_ASSERT(status, "Failed ot initalize Glad!");

		AW_CORE_INFO("OpenGl Renderer");
		AW_CORE_INFO("  Vendor     {0}", glGetString(GL_VENDOR));
		AW_CORE_INFO("  Renderer   {0}", glGetString(GL_RENDERER));
		AW_CORE_INFO("  Version    {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers() {

		glfwSwapBuffers(windowHandle);
	}
}