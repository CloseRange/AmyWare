#pragma once

#include "AmyWare/Core/Layer.h"
#include "AmyWare/Events/KeyEvent.h"
#include "AmyWare/Events/MouseEvent.h"
#include "AmyWare/Events/ApplicationEvent.h"

namespace AmyWare {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;

	};
}

