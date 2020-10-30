#pragma once

#include "AmyWare.h"

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
		OrthographicCameraController camera;
		Ref<Texture2D> texture;
		Ref<Texture2D> textureMap;
		Ref<SubTexture2D> subTexTree;
		Ref<FrameBuffer> frameBuffer;
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		Drawable drawQuads[20 * 20];
		bool viewportFocused = false, viewportHovered = false;
		glm::vec2 viewportSize{ 0.0f, 0.0f };

	};
}
