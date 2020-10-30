#pragma once
#include "AmyWare/Core/Core.h"

namespace AmyWare {
	class Input {
	public:
		static bool IsKeyDown(int keycode);

		static bool IsMouseDown(int keycode);
		static std::pair<float, float> GetMouse();
		static float GetMouseY();
		static float GetMouseX();
	};
}

