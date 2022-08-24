#pragma once

#ifdef RX_PLATFORM_WINDOWS

extern Rexal::Application* Rexal::CreateApplication();

int main(int argc, char** argv)
{
	Rexal::Log::Init();
	RX_CORE_WARN("Initialized Log");
	int a = 6;
	RX_INFO("Hello Bro Var={0}", a);
	auto app = Rexal::CreateApplication();
	app->Run();
	delete app;
}

#endif