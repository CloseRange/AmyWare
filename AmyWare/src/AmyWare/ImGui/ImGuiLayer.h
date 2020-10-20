#pragma once

#include "AmyWare/Layer.h"
#include "AmyWare/Events/KeyEvent.h"
#include "AmyWare/Events/MouseEvent.h"
#include "AmyWare/Events/ApplicationEvent.h"

namespace AmyWare {
	class AW_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;

	};
}

