#pragma once

#include "Core.h"

#include "Window.h"
#include "AmyWare/LayerStack.h"
#include "AmyWare/Events/Event.h"
#include "AmyWare/Events/ApplicationEvent.h"

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
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* Instance;
	};

	Application* CreateApplication();
}
