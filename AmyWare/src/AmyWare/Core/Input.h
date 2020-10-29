#pragma once
#include "AmyWare/Core/Core.h"

namespace AmyWare {
	class AW_API Input {
	public:
		inline static bool IsKeyDown(int keycode) { return instance->IsKeyPressedImpl(keycode); };

		inline static bool IsMouseDown(int keycode) { return instance->IsMouseButtonImpl(keycode); };
		inline static std::pair<float, float> GetMouse() { return instance->GetMouseImpl(); };
		inline static float GetMouseX() { return instance->GetMouseXImpl(); };
		inline static float GetMouseY() { return instance->GetMouseYImpl(); };

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonImpl(int keycode) = 0;
		virtual std::pair<float, float> GetMouseImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* instance;
	};
}

