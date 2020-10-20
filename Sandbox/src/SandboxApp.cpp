
#include <AmyWare.h>
#include <sstream>

#include "imgui/imgui.h"

class ExLayer : public AmyWare::Layer {
public:
	ExLayer() : Layer("Example") {}
	void OnUpdate() override {
	}
	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
	void OnEvent(AmyWare::Event& event) override {
		// AW_TRACE("{0} hi", event.ToString());
		if (event.GetEventType() == AmyWare::EventType::KeyPressed) {
			AmyWare::KeyPressedEvent& e = (AmyWare::KeyPressedEvent&) event;
			AW_TRACE("{0}", (char)e.GetKeyCode());

		}
	}
};

class Sandbox : public AmyWare::Application {
public:
	Sandbox() {
		PushLayer(new ExLayer());
	}
	~Sandbox() {

	}
};

AmyWare::Application* AmyWare::CreateApplication() {
	return new Sandbox();
}

