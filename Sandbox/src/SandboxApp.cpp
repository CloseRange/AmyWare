#include <AmyWare.h>

class Sandbox : public AmyWare::Application {
public:
	Sandbox() {
	
	}
	~Sandbox() {

	}
};


AmyWare::Application* AmyWare::CreateApplication() {
	printf("Hello Guys and gals!");
	return new Sandbox();
}
