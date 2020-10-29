#pragma once
#ifdef AW_PLATFORM_WINDOWS

extern AmyWare::Application* AmyWare::CreateApplication();



int main(int argc, char** argv) {
	AmyWare::Log::Init();
	AmyWare::Drawable::Init();

	AW_PROFILE_BEGIN_SESSION("Startup", "AmyWareProfile-Startup.json");
	auto app = AmyWare::CreateApplication();
	AW_PROFILE_END_SESSION();

	AW_PROFILE_BEGIN_SESSION("Runtime", "AmyWareProfile-Runtime.json");
	app->Run();
	AW_PROFILE_END_SESSION();

	AW_PROFILE_BEGIN_SESSION("Shutdown", "AmyWareProfile-Shutdown.json");
	delete app;
	AW_PROFILE_END_SESSION();

}


#endif
