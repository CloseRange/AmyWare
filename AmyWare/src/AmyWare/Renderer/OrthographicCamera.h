#pragma once

#include <glm/glm.hpp>

namespace AmyWare {


	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position) { this->position = position; CalcViewMatrix(); }
		void SetRotation(float rotation) { this->rotation = rotation; CalcViewMatrix(); }

		const glm::vec3& GetPosition() { return position; }
		float GetRotation() { return rotation; }


		const glm::mat4& GetProjection() const { return projectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return viewMatrix; }
		const glm::mat4& GetViewProjection() const { return viewProjectionMatrix; }
	private:
		void CalcViewMatrix();

		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;
	};
}

