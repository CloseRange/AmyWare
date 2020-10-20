
#include <AmyWare.h>
#include <sstream>

class ExLayer : public AmyWare::Layer {
public:
	ExLayer() : Layer("Example") {}
	void OnUpdate() override {
		// AW_INFO("ExLayer::Update");
	}
	void OnEvent(AmyWare::Event& event) override {
		// AW_TRACE("{0} hi", event.ToString());
	}
};

class Sandbox : public AmyWare::Application {
public:
	Sandbox() {
		PushLayer(new ExLayer());
		PushOverlay(new AmyWare::ImGuiLayer());
	}
	~Sandbox() {

	}
};

AmyWare::Application* AmyWare::CreateApplication() {
	return new Sandbox();
}

