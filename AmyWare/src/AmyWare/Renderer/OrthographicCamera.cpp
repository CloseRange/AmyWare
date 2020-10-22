#include "awpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace AmyWare {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : viewMatrix(1.0f) {
		projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
	void OrthographicCamera::CalcViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
		viewMatrix = glm::inverse(transform);

		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}