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

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};
}

