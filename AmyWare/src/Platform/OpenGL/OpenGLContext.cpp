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
	}
	void OpenGLContext::SwapBuffers() {

		glfwSwapBuffers(windowHandle);
	}
}