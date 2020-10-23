#include "awpch.h"
#include "OrthographicCameraController.h"

#include "AmyWare/Input.h"
#include "AmyWare/KeyCodes.h"

namespace AmyWare {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
		: aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio* zoomLevel, -zoomLevel, zoomLevel) {
		allowRotation = rotation;
	}
	void OrthographicCameraController::OnUpdate(Timestep ts) {
		if (Input::IsKeyDown(AW_KEY_A))
			camPosition.x -= camMoveSpeed * ts;
		if (Input::IsKeyDown(AW_KEY_D))
			camPosition.x += camMoveSpeed * ts;

		if (Input::IsKeyDown(AW_KEY_W))
			camPosition.y += camMoveSpeed * ts;
		if (Input::IsKeyDown(AW_KEY_S))
			camPosition.y -= camMoveSpeed * ts;

		if (allowRotation) {
			if (Input::IsKeyDown(AW_KEY_Q))
				camRotation += camRotationSpeed * ts;
			if (Input::IsKeyDown(AW_KEY_E))
				camRotation -= camRotationSpeed * ts;
			camera.SetRotation(camRotation);
		}
		camera.SetPosition(camPosition);
	}
	void OrthographicCameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(AW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(AW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		zoomLevel -= e.GetYOffset() * zoomRate;
		zoomLevel = std::max(zoomLevel, 0.25f);
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
		aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}
}