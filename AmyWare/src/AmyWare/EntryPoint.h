#pragma once

#ifdef AW_PLATFORM_WINDOWS

extern AmyWare::Application* AmyWare::CreateApplication();

int main(int argc, char** argv) {
	AmyWare::Log::Init();
	AW_CORE_WARN("Woah that went badly..");
	int a = 5;
	AW_INFO("Woah Var={0}", a);

	auto app = AmyWare::CreateApplication();
	app->Run();
	delete app;
}

#endif
