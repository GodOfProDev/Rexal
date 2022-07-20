#include <Rexal.h>

class ExampleLayer : public Rexal::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//RX_INFO("ExampleLayer::Update");
	}

	void OnEvent(Rexal::Event& event) override
	{
		//RX_TRACE("{0}", event);
	}

};

class Sandbox : public Rexal::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Rexal::Application* Rexal::CreateApplication()
{
	return new Sandbox();
}