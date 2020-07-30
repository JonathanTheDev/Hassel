#include <Hassel.h>

class ExampleLayer : public Hassel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		HSL_INFO("ExmapleLayer::Update");
	}

	void OnEvent(Hassel::Event& event) override
	{
		HSL_TRACE("{0}", event);
	}
};

class Sandbox : public Hassel::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Hassel::Application* Hassel::CreateApplication()
{
	return new Sandbox();
}
