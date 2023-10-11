#pragma once
#include "Rexal/Core/Base.h"

#ifdef RX_PLATFORM_WINDOWS

extern Rexal::Application* Rexal::CreateApplication();

int main(int argc, char** argv)
{
	Rexal::Log::Init();

	RX_PROFILE_BEGIN_SESSION("Startup", "RexalProfile-Startup.json");
	auto app = Rexal::CreateApplication();
	RX_PROFILE_END_SESSION();

	RX_PROFILE_BEGIN_SESSION("Runtime", "RexalProfile-Runtime.json");
	app->Run();
	RX_PROFILE_END_SESSION();

	RX_PROFILE_BEGIN_SESSION("Shutdown", "RexalProfile-Shutdown.json");
	delete app;
	RX_PROFILE_END_SESSION();
}

#endif