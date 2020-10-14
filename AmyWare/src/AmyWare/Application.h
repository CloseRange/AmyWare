#pragma once

#include "Core.h"

namespace AmyWare {
	class AW_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

