#pragma once

#include "Core.h"

namespace Hassel {

	class HASSEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	/// <summary>
	/// To be defined in CLIENT
	/// </summary>
	/// <returns>Application to  use as entrypoint</returns>
	Application* CreateApplication();

}
