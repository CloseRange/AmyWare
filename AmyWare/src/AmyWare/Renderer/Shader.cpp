#include "awpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace AmyWare {
	Ref<Shader> Shader::Create(const std::string& filepath) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	    AW_CORE_ASSERT(false, "RendererAPI::None isn't yet supported");
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(filepath);
		}
		AW_CORE_ASSERT(false, "RendererAPI is uknown");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	    AW_CORE_ASSERT(false, "RendererAPI::None isn't yet supported");
			case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		AW_CORE_ASSERT(false, "RendererAPI is uknown");
		return nullptr;
	}
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		AW_CORE_ASSERT(!Exists(name), "Shader already exists!");
		shaders[name] = shader;
	}
	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		auto& name = shader->GetName();
		AW_CORE_ASSERT(shaders.find(name) == shaders.end(), "Shader already exists!");
		shaders[name] = shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return Ref<Shader>();
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		AW_CORE_ASSERT(Exists(name), "Shader not found!");
		return shaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const {
		return shaders.find(name) != shaders.end();
	}
}
