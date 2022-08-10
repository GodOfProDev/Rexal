#pragma once

#include <memory>

#ifdef RX_PLATFORM_WINDOWS
#if RX_DYNAMIC_LINK
	#ifdef RX_BUILD_DLL
		#define REXAL_API __declspec(dllexport)
	#else
		#define REXAL_API __declspec(dllimport)
	#endif
#else
	#define REXAL_API
#endif
#else
	#error Rexal only supports Windows!
#endif

#ifdef RX_DEBUG
	#define RX_ENABLE_ASSERTS
#endif

#ifdef RX_ENABLE_ASSERTS
	#define RX_ASSERT(x, ...) { if(!(x)) { RX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RX_CORE_ASSERT(x, ...) { if(!(x)) { RX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RX_ASSERT(x, ...)
	#define RX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define RX_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Rexal {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}