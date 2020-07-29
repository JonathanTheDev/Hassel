#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hassel {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("Hassel");
		
		s_ClientLogger = spdlog::stdout_color_mt("App");

		Log::GetCoreLogger()->set_level(spdlog::level::trace);
		Log::GetClientLogger()->set_level(spdlog::level::trace);
	}
}