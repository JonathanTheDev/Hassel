#pragma once

#ifdef HASSEL_PLATFORM_WINDOWS

extern Hassel::Application* Hassel::CreateApplication();

int main(int argc, char** argv)
{
	Hassel::Log::Init();

	HSL_CORE_WARN("Initialized Log!");

	auto app = Hassel::CreateApplication();
	app->Run();
	delete app;
}

#else
#error Hassel only support Windows!
#endif // HASSEL_PLATFORM_WINDOWS