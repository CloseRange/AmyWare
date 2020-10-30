#pragma once

#include "Core.h"

#include "Window.h"
#include "AmyWare/Core/LayerStack.h"
#include "AmyWare/Events/Event.h"
#include "AmyWare/Events/ApplicationEvent.h"

#include "AmyWare/Utility/Timestep.h"

#include "AmyWare/ImGui/ImGuiLayer.h"

namespace AmyWare {
	class Application {
	public:
		Application(const std::string& name = "Amy App");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Close() {
			m_Running = false;
		}

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		bool OnWindowClosed(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		bool minimized = false;

		float lastFrameTime = 0.0f;

		static Application* Instance;
		

	};

	Application* CreateApplication();
}

