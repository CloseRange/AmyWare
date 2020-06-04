#include "awpch.h"
#include "Application.h"

#include "AmyWare/Events/Event.h"
#include "AmyWare/Events/ApplicationEvent.h"
#include "AmyWare/Log.h"

namespace AmyWare {

	Application::Application() {
	}


	Application::~Application() {
	}
	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		AW_TRACE(e);


		while (true);
	}
}
