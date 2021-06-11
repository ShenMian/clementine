// Copyright 2021 SMS
// License(Apache-2.0)

#include "Main.h"
#include "Clem.h"
#include <map>
#include <string>

using namespace std::chrono_literals;

int main_(int argc, char* argv[])
{
	clem::Main main;
	return main.main(argc, argv);
}

namespace clem
{

Main::Main()
{
	init();
}

Main::~Main()
{
	deinit();
}

int Main::main(int argc, char* argv[])
{
	parseArgs(argc, argv);

	auto& app = Application();

	app.init();
	app.run();
	app.deinit();

  return 0;
}

void Main::run()
{
	mainLoop();
}

void Main::stop()
{
	running = false;
}

void Main::pause()
{
	paused = true;
}

void Main::mainLoop()
{
	long previous = getCurrentMillSecond();

	running = true;
	while(running)
	{
		auto     current = getCurrentMillSecond();
		uint16_t dt      = static_cast<uint16_t>(current - previous);
		previous         = current;

		updateInput(dt);
		updateScene(dt);
		renderScene(dt);

		updateFrameRate(dt);

		while(paused)
		{
			std::this_thread::sleep_for(500ms);
			previous = getCurrentMillSecond();
		}
	}
}

void Main::parseArgs(int argc, char* argv[])
{
	std::map<std::string, std::string> args;

	std::string_view str;
	for(int i = 1; i < argc; i++)
{
		str      = argv[i];
		auto it  = str.find('=');
		auto opt = str.substr(0, it);
		auto val = str.substr(it + 1);
		args.emplace(opt, val);
}

	args.clear();
}

void Main::resume()
{
	paused = false;
}

void Main::init()
{
	Logger::create("core");
	Logger::create("audio");
	Logger::create("assert");
	Logger::create("networking");

	Audio::init();
	Keyboard::init();
}

void Main::deinit()
{
	Keyboard::deinit();
	Audio::deinit();
}

#ifdef OS_UNIX

void Main::platformInit()
{
}

#	include <sys/time.h>

long Main::getCurrentMillSecond() const
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec * 0.001;
}

#endif

#ifdef OS_WIN

void Main::platformInit()
{
	DWORD mode;

	const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(!GetConsoleMode(hOut, &mode))
		assert(false);
	// mode &= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // 启用 VT100 模式 // TODO: Win10 以下會失敗
	if(!SetConsoleMode(hOut, mode))
		assert(false);

	const auto hIn = GetStdHandle(STD_INPUT_HANDLE);
	if(!GetConsoleMode(hIn, &mode))
		assert(false);
	mode &= ~ENABLE_QUICK_EDIT_MODE; // 禁用 快速编辑模式
	if(!SetConsoleMode(hIn, mode))
		assert(false);
}

long Main::getCurrentMillSecond() const
{
	static LARGE_INTEGER freq;
	static BOOL          ret = QueryPerformanceFrequency(&freq);
	CLEM_ASSERT_TRUE(ret != 0, "the installed hardware doesn't supports a high-resolution performance counter");

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return (long)(time.QuadPart * 1000 / freq.QuadPart);
}

#endif

} // namespace clem
