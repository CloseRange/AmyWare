#pragma once

#include "AMyWare/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace AmyWare {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};
}

