#include "awpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace AmyWare {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	AW_CORE_ASSERT(false, "RendererAPI::None isn't yet supported");
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		AW_CORE_ASSERT(false, "RendererAPI is uknown");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	AW_CORE_ASSERT(false, "RendererAPI::None isn't yet supported");
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}
		AW_CORE_ASSERT(false, "RendererAPI is uknown");
		return nullptr;
	}
}

