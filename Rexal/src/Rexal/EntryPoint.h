#pragma once

#ifdef RX_PLATFORM_WINDOWS

extern Rexal::Application* Rexal::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Rexal::CreateApplication();
	app->Run();
	delete app;
}

#endif