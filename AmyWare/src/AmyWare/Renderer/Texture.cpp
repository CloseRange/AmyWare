#include "awpch.h"
#include "Texture.h"
#include "AmyWare/Core.h"
#include <string>

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace AmyWare {
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	    AW_CORE_ASSERT(false, "RendererAPI::None isn't yet supported");
			case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>(path);
		}
		AW_CORE_ASSERT(false, "RendererAPI is uknown");
		return nullptr;
	}
}
