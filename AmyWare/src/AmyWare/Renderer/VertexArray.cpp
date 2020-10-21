#include "awpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace AmyWare {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	    AW_CORE_ASSERT(false, "RendererAPI::None isn't yet supported");
			case RendererAPI::API::OpenGL:		return new OpenGLVertexArray();
		}
		AW_CORE_ASSERT(false, "RendererAPI is uknown");
		return nullptr;
	}
}