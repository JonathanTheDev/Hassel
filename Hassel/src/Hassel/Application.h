#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Hassel {

	class HASSEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window>  m_Window;
		bool m_Running = true;
	};

	/// <summary>
	/// To be defined in CLIENT
	/// </summary>
	/// <returns>Application to  use as entrypoint</returns>
	Application* CreateApplication();

}
