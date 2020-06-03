#pragma once

#ifdef AW_PLATFORM_WINDOWS
	#ifdef AW_BUILD_DLL
		#define AMYWARE_API __declspec(dllexport)
	#else
		#define AMYWARE_API __declspec(dllimport)
	#endif
#else
#error AmyWare only works on Windows.
#endif
