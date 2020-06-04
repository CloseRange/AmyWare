#include <AmyWare.h>

class Sandbox : public AmyWare::Application {
public:
	Sandbox() {
	
	}
	~Sandbox() {

	}
};


AmyWare::Application* AmyWare::CreateApplication() {
	return new Sandbox();
}
