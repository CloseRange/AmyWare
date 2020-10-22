#pragma once

#include "Core.h"

#include "Window.h"
#include "AmyWare/LayerStack.h"
#include "AmyWare/Events/Event.h"
#include "AmyWare/Events/ApplicationEvent.h"

#include "AmyWare/Core/Timestep.h"

#include "AmyWare/ImGui/ImGuiLayer.h"

namespace AmyWare {
	class Application {
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

		float lastFrameTime = 0.0f;

		static Application* Instance;
		

	};

	Application* CreateApplication();
}

