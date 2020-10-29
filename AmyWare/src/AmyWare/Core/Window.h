#pragma once

#include "awpch.h"

#include "AmyWare/Core/Core.h"
#include "AmyWare/Events/Event.h"

namespace AmyWare {
	struct WindowProps {
		std::string Title;
		uint32_t Width, Height;


		WindowProps(const std::string& title = "AmyWare Engine", uint32_t width = 1280, uint32_t height = 720) {
			Title = title;
			Width = width;
			Height = height;
		}
	};


	class AW_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}

