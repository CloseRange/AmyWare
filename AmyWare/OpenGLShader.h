#pragma once
#include "AmyWare/Renderer/Shader.h"

#include <string>
#include <glm/glm.hpp>

namespace AmyWare {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
	private:
		uint32_t rendererID;
	};
}

