#pragma once
#include "AmyWare/Core.h"

#include <string>
#include "AmyWare/Renderer/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace AmyWare {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override;

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
	private:
		void Compile(std::unordered_map<GLenum, std::string> sources);
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		uint32_t RendererID;
		std::string name;
	};
}
