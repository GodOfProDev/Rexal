#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Rexal {
	class REXAL_API Log
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
#define RX_CORE_TRACE(...)    ::Rexal::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RX_CORE_INFO(...)     ::Rexal::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RX_CORE_WARN(...)     ::Rexal::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RX_CORE_ERROR(...)    ::Rexal::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RX_CORE_CRITICAL(...)    ::Rexal::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define RX_TRACE(...)         ::Rexal::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RX_INFO(...)          ::Rexal::Log::GetClientLogger()->info(__VA_ARGS__)
#define RX_WARN(...)          ::Rexal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RX_ERROR(...)         ::Rexal::Log::GetClientLogger()->error(__VA_ARGS__)
#define RX_CRITICAL(...)         ::Rexal::Log::GetClientLogger()->critical(__VA_ARGS__)