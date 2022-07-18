#include <Rexal.h>

class Sandbox : public Rexal::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};

Rexal::Application* Rexal::CreateApplication()
{
	return new Sandbox();
}