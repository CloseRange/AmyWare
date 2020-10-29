#include "awpch.h"
#include "FrameBuffer.h"
#include "AmyWare/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace AmyWare {
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	    AW_CORE_ASSERT(false, "RendererAPI::None isn't yet supported");
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLFrameBuffer>(spec);
		}
		AW_CORE_ASSERT(false, "RendererAPI is uknown");
		return nullptr;
	}
}

