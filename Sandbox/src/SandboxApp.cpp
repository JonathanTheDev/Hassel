#include <Hassel.h>

class Sandbox : public Hassel::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Hassel::Application* Hassel::CreateApplication()
{
	return new Sandbox();
}