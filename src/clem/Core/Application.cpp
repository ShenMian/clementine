
#include "Application.h"
#include "clem/log.h"
#include "clem/Profiler.h"
#include "clem/platform.h"
#include "clem.h"

using std::string;

int main(int argc, char* argv[])
{
	auto app = CreateApplication();
	Director::getInstance()->run();
	delete app;
	return 0;
}

Application* Application::instance = nullptr;

Application& Application::getInstance()
{
	assert(instance);
	return *instance;
}

Application::Application(const string& name)
		: name(name)
{
	if(instance != nullptr)
	{
		CLEM_CORE_CRITICAL("create the second application is not allowed");
		abort();
	}
	instance = this;
	Log::init();
	PROFILE_SESSION_BEGIN();
	PROFILE_FUNC();

	// width / height = 80 / 25 => width * 25 = height * 80
	const short width  = 80;
	const short height = width * 25 / 80;
	frameBuffer.setSize({width, height});

#ifdef OS_WIN
	// ¿ªÆô VT100 Ä£Ê½
	const auto hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD      mode;
	if(!GetConsoleMode(hStdOut, &mode))
		assert(false);
	if(!SetConsoleMode(hStdOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
		assert(false);
#endif
}

Application::~Application()
{
	PROFILE_SESSION_END();
}

const std::string& Application::getName() const
{
	return name;
}
