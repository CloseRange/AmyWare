#pragma once
#include "AmyWare/Core/Core.h"
#include "AmyWare/Core/Input.h"

namespace AmyWare {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonImpl(int keycode) override;
		virtual std::pair<float, float> GetMouseImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}

