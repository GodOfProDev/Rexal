#pragma once

#include <memory>

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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}