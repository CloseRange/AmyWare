#pragma once

#include "Core.h"

namespace AmyWare {

	class AMYWARE_API Application {
		public:
			Application();
			virtual ~Application();
			void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

