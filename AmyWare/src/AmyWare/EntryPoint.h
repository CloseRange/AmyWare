#pragma once

#ifdef AW_PLATFORM_WINDOWS

extern AmyWare::Application* AmyWare::CreateApplication();

int main(int argc, char** argv) {
	auto app = AmyWare::CreateApplication();
	app->Run();
	delete app;
}

#endif
