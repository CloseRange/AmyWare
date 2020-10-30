#pragma once
#include "AmyWare/Renderer/OrthographicCamera.h"
#include "AmyWare/Utility/Timestep.h"

#include "AmyWare/Events/ApplicationEvent.h"
#include "AmyWare/Events/MouseEvent.h"

namespace AmyWare {


	struct OrthographicCameraBounds {
		float Left, Right, Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation=false);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void Resize(float width, float height);

		OrthographicCamera& GetCamera() { return camera; }
		const OrthographicCamera& GetCamera() const { return camera; }
		float GetZoomLevel() { return zoomLevel; }
		void SetZoomLevel(float level) { zoomLevel = level; CalculateView(); }

		const OrthographicCameraBounds& GetBounds() const { return bounds; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		void CalculateView();
		float aspectRatio;
		float zoomLevel = 1.0f;
		float zoomRate = 0.5f;
		OrthographicCameraBounds bounds;
		OrthographicCamera camera;

		glm::vec3 camPosition = { 0.0f, 0.0f, 0.0f };
		float camRotation = 0.0f;
		float camMoveSpeed = 1.0f;
		float camRotationSpeed = 1.0f;

		bool allowRotation;
	};
}

