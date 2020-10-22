#pragma once
#include "AmyWare/Core.h"

#include <string>
#include <glm/glm.hpp>

namespace AmyWare {

	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t rendererID;

	};
}

