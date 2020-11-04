#pragma once

#include "AmyWare.h"
#include "Panels/SceneHierarchyPanel.h"

namespace AmyWare {
	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;


		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
		void SaveScene();

		OrthographicCameraController camera;
		Ref<FrameBuffer> frameBuffer;

		Ref<Scene> activeScene;
		Entity square;
		Entity cameraEntity, cameraEntity2;

		bool viewportFocused = false, viewportHovered = false;
		glm::vec2 viewportSize{ 0.0f, 0.0f };

		// Panels
		SceneHierarchyPanel scenePanel;

	};
}
