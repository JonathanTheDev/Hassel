#pragma once

#include "Hassel/Layer.h"

#include "Hassel/Events/ApplicationEvent.h"
#include "Hassel/Events/KeyEvent.h"
#include "Hassel/Events/MouseEvent.h"

namespace Hassel
{
	class HASSEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetatch();
		void OnUpdate();
		void OnEvent(Event& event);
	
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		static const char* GetClipboardText(void* user_data);
		static void SetClipboardText(void* user_data, const char* text);

		float m_Time = 0.0f;
	};
}