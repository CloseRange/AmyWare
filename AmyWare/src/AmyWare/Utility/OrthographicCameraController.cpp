#include "awpch.h"
#include "OrthographicCameraController.h"

#include "AmyWare/Core/Input.h"
#include "AmyWare/Core/KeyCodes.h"

namespace AmyWare {
	OrthographicCameraController::OrthographicCameraController(float _aspectRatio, bool rotation) 
		: aspectRatio(_aspectRatio), bounds({ -aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel }), camera(bounds.Left, bounds.Right, bounds.Bottom, bounds.Top) {
		allowRotation = rotation;
	}
	void OrthographicCameraController::OnUpdate(Timestep ts) {
		AW_PROFILE_FUNCTION();

		if (Input::IsKeyDown(KeyCode::A))
			camPosition.x -= camMoveSpeed * ts;
		if (Input::IsKeyDown(KeyCode::D))
			camPosition.x += camMoveSpeed * ts;

		if (Input::IsKeyDown(KeyCode::W))
			camPosition.y += camMoveSpeed * ts;
		if (Input::IsKeyDown(KeyCode::S))
			camPosition.y -= camMoveSpeed * ts;

		if (allowRotation) {
			if (Input::IsKeyDown(KeyCode::Q))
				camRotation += camRotationSpeed * ts;
			if (Input::IsKeyDown(KeyCode::E))
				camRotation -= camRotationSpeed * ts;
			camera.SetRotation(camRotation);
		}
		camera.SetPosition(camPosition);
	}
	void OrthographicCameraController::OnEvent(Event& e) {
		AW_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(AW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(AW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		AW_PROFILE_FUNCTION();

		zoomLevel -= e.GetYOffset() * zoomRate;
		zoomLevel = std::max(zoomLevel, 0.25f);
		CalculateView();
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
		AW_PROFILE_FUNCTION();
		
		Resize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
	void OrthographicCameraController::Resize(float width, float height) {
		aspectRatio = width / height;
		CalculateView();
	}
	void OrthographicCameraController::CalculateView() {
		bounds = { -aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel };
		camera.SetProjection(bounds.Left, bounds.Right, bounds.Bottom, bounds.Top);
	}
}