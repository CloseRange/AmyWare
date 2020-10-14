#pragma once

#ifdef AW_PLATFORM_WINDOWS
	#ifdef AW_BUILD_DLL
		#define AW_API __declspec(dllexport)
	#else
		#define AW_API __declspec(dllimport)
	#endif
#else
#error AmyWare only supports Windows!
#endif

