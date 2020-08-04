#include <Hassel.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

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

		if (Hassel::Input::IsKeyPressed(HSL_KEY_B))
		{
			HSL_TRACE("B key pressed!");
		}
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
		PushOverlay(new Hassel::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Hassel::Application* Hassel::CreateApplication()
{
	return new Sandbox();
}
