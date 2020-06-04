#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace AmyWare {
	class AMYWARE_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

/// CORE LOG MACROS
#define AW_CORE_TRACE(...)   ::AmyWare::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AW_CORE_INFO(...)    ::AmyWare::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AW_CORE_WARN(...)    ::AmyWare::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AW_CORE_ERROR(...)   ::AmyWare::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AW_CORE_FATAL(...)   ::AmyWare::Log::GetCoreLogger()->fatal(__VA_ARGS__)

/// CLIENT LOG MACROS
#define AW_TRACE(...)		 ::AmyWare::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AW_INFO(...)		 ::AmyWare::Log::GetClientLogger()->info(__VA_ARGS__)
#define AW_WARN(...)		 ::AmyWare::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AW_ERROR(...)		 ::AmyWare::Log::GetClientLogger()->error(__VA_ARGS__)
#define AW_FATAL(...)		 ::AmyWare::Log::GetClientLogger()->fatal(__VA_ARGS__)
