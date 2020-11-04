#include "awpch.h"
#include "AmyWare/Core/Input.h"

#include "AmyWare/Core/Application.h"
#include <GLFW/glfw3.h>

namespace AmyWare {


	bool Input::IsKeyDown(KeyCode keycode) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, (uint32_t)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Input::IsMouseDown(MouseCode button) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, (uint32_t)button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> Input::GetMouse() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
	float Input::GetMouseX() {
		auto [x, y] = GetMouse();
		return x;
	}
	float Input::GetMouseY() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto [x, y] = GetMouse();
		return y;
	}
}