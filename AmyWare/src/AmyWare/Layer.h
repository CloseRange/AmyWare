#pragma once
#include "AmyWare/Core.h"
#include "AmyWare/Events/Event.h"

#include "AmyWare/Core/Timestep.h"

namespace AmyWare {
	class AW_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();


		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

