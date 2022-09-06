#include <Rexal.h>
#include <Rexal/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Rexal::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Rexal::Application* Rexal::CreateApplication()
{
	return new Sandbox();
}