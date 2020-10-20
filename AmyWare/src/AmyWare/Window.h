#pragma once

#include "awpch.h"

#include "AmyWare/Core.h"
#include "Events/Event.h"

namespace AmyWare {
	struct WindowProps {
		std::string Title;
		unsigned int Width, Height;


		WindowProps(const std::string& title = "AmyWare Engine", unsigned int width = 1280, unsigned int height = 720) {
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
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		static Window* Create(const WindowProps& props = WindowProps());
	};
}

