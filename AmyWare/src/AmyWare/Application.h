#pragma once

#include "Core.h"

#include "Window.h"
#include "AmyWare/LayerStack.h"
#include "AmyWare/Events/Event.h"
#include "AmyWare/Events/ApplicationEvent.h"

#include "AmyWare/ImGui/ImGuiLayer.h"

#include "AmyWare/Renderer/Shader.h"
#include "AmyWare/Renderer/Buffer.h"
#include "AmyWare/Renderer/VertexArray.h"


namespace AmyWare {
	class AW_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* Instance;

		std::shared_ptr<Shader> shader;
		std::shared_ptr<Shader> shader2;
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<VertexArray> squareVA;
	};

	Application* CreateApplication();
}

