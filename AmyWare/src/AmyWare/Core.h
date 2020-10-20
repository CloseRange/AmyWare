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

#ifdef AW_DEBUG
	#define AW_ENDABLE_ASSERTS
#endif

#ifdef AW_ENABLE_ASSERTS
	#define AW_ASSERT(x, ...) {if(!(x)) { AW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define AW_CORE_ASSERT(x, ...) {if(!(x)) { AW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define AW_ASSERT(x, ...) 
	#define AW_CORE_ASSERT(x, ...) 
#endif


#define BIT(x) (1 << x)
#define AW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1
