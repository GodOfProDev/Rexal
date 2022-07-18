#pragma once

#ifdef RX_PLATFORM_WINDOWS
	#ifdef RX_BUILD_DLL
		#define REXAL_API __declspec(dllexport)
	#else
		#define REXAL_API __declspec(dllimport)
	#endif
#else
	#error Rexal only supports Windows!
#endif