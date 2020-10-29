#include "awpch.h"
#include "Application.h"

#include "AmyWare/Renderer/Renderer.h"

#include "AmyWare/Utility/Log.h"

#include <GLFW/glfw3.h>

namespace AmyWare {
#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;


	Application::Application(const std::string& name) {
		AW_PROFILE_FUNCTION();

		AW_CORE_ASSERT(!Instance, "Application already defined")
		Instance = this;
		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(BIND_EVENT(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		// Palette::ApplyToGui(Palette::AmyPalette);
	}
	Application::~Application() {
		AW_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}
	void Application::OnEvent(Event& e) {
		AW_PROFILE_FUNCTION();

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
		AW_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		AW_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::Run() {
		AW_PROFILE_SCOPE("Game");

		while (m_Running) {
			AW_PROFILE_SCOPE("Run Loop");
			float time = (float) glfwGetTime(); // Platform::GetTime
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;

			if (!minimized) {
				{
					AW_PROFILE_SCOPE("Run Loop : Stack Update");
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
			}

			m_ImGuiLayer->Begin();
			{
				AW_PROFILE_SCOPE("Run Loop : Stack ImGui");
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}
	}
	bool Application::OnWindowClosed(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& event) {
		AW_PROFILE_FUNCTION();
		if (event.GetWidth() == 0 || event.GetHeight() == 0) {
			minimized = true;
			return false;
		}
		minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}
}