#include "hslpch.h"
#include "WindowsInput.h"

#include "Hassel/Application.h"
#include <GLFW/glfw3.h>

namespace Hassel
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [xPos, yPos] = GetMousePositionImpl();

		return xPos;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [xPos, yPos] = GetMousePositionImpl();

		return yPos;
	}
	std::tuple<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return std::tuple<float, float>((float)xPos, (float)yPos);
	}
}


