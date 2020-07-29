#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Hassel {

	class HASSEL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define HSL_CORE_TRACE(...)		::Hassel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HSL_CORE_INFO(...)		::Hassel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HSL_CORE_WARN(...)		::Hassel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HSL_CORE_ERROR(...)		::Hassel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HSL_CORE_CRITICAL(...)	::Hassel::Log::GetCoreLogger()->critical(__VA_ARGS__)


// Client log macros
#define HSL_TRACE(...)		::Hassel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HSL_INFO(...)		::Hassel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HSL_WARN(...)		::Hassel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HSL_ERROR(...)		::Hassel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HSL_CRITICAL(...)	::Hassel::Log::GetClientLogger()->critical(__VA_ARGS__)