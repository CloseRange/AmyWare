#include "awpch.h"
#include "Application.h"

#include "AmyWare/Renderer/Renderer.h"

#include "AmyWare/Log.h"

#include <GLFW/glfw3.h>

namespace AmyWare {
#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;


	Application::Application() {

		AW_CORE_ASSERT(!Instance, "Application already defined")
		Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		// Palette::ApplyToGui(Palette::AmyPalette);
	}
	Application::~Application() {

	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(OnWindowResize));



		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			auto l = (*--it);
			l->OnEvent(e);
			if (e.Handled) break;
		}
	}
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::Run() {

		while (m_Running) {
			float time = (float) glfwGetTime(); // Platform::GetTime
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;

			if(!minimized)
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}
	}
	bool Application::OnWindowClosed(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& event) {
		if (event.GetWidth() == 0 || event.GetHeight() == 0) {
			minimized = true;
			return false;
		}
		minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}
}