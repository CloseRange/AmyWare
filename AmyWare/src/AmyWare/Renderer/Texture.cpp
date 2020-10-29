#include "awpch.h"
#include "Texture.h"
#include "AmyWare/Core/Core.h"
#include <string>

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace AmyWare {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	    AW_CORE_ASSERT(false, "RendererAPI::None isn't yet supported");
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, height);
		}
		AW_CORE_ASSERT(false, "RendererAPI is uknown");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	    AW_CORE_ASSERT(false, "RendererAPI::None isn't yet supported");
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(path);
		}
		AW_CORE_ASSERT(false, "RendererAPI is uknown");
		return nullptr;
	}
}
