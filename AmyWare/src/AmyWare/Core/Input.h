#pragma once

#include "AmyWare/Core/KeyCodes.h"
#include "AmyWare/Core/MouseCodes.h"


namespace AmyWare {
	class Input {
	public:
		static bool IsKeyDown(KeyCode keycode);

		static bool IsMouseDown(MouseCode keycode);
		static std::pair<float, float> GetMouse();
		static float GetMouseY();
		static float GetMouseX();
	};
}

