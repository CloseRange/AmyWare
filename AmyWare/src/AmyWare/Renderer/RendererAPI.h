#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace AmyWare {
	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		};
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetActive() { return active; }
	private:
		static API active;
	};
}

