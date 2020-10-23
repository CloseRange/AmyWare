#pragma once
#include "AmyWare/Renderer/OrthographicCamera.h"
#include "AmyWare/Core/Timestep.h"

#include "AmyWare/Events/ApplicationEvent.h"
#include "AmyWare/Events/MouseEvent.h"

namespace AmyWare {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation=false);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		OrthographicCamera& GetCamera() { return camera; }
		const OrthographicCamera& GetCamera() const { return camera; }
		float GetZoomLevel() { return zoomLevel; }
		void SetZoomLevel(float level) { zoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		float aspectRatio;
		float zoomLevel = 1.0f;
		float zoomRate = 0.5f;
		OrthographicCamera camera;

		glm::vec3 camPosition = { 0.0f, 0.0f, 0.0f };
		float camRotation = 0.0f;
		float camMoveSpeed = 1.0f;
		float camRotationSpeed = 1.0f;

		bool allowRotation;
	};
}

