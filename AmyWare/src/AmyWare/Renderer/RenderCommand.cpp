#include "awpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace AmyWare {
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}
