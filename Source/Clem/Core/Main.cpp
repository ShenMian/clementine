// Copyright 2021 SMS
// License(Apache-2.0)

#include "Main.h"
#include "Application.h"

#include "Clem/Assert.h"
#include "Clem/Audio/Audio.h"
#include "Clem/Components/ScriptSystem.h"
#include "Clem/Core/Input/Keyboard.h"
#include "Clem/Core/Input/Mouse.h"
#include "Clem/ECS/Registry.h"
#include "Clem/Logger.h"
#include "Clem/Physics/Physics.h"
#include "Clem/Profiler.h"
#include "Clem/Rendering/Rendering.h"
#include "Clem/Window.h"
#include <map>
#include <string>

using namespace std::chrono_literals;
using clem::Main;

int main(int argc, char* argv[])
{
	Main::init();
	const auto ret = Main::main(argc, argv);
	Main::deinit();
	return ret;
}

namespace clem
{

Registry     Main::registry;
bool         Main::running     = false;
bool         Main::paused      = false;
uint16_t     Main::msPerInput  = 16;
uint16_t     Main::msPerUpdate = 16;
uint16_t     Main::msPerRender = 16;
uint16_t     Main::frameRate   = 0;
Application* Main::app         = nullptr;

int Main::main(int argc, char* argv[])
{
	parseArgs(argc, argv);

	app = CreateApplication();
	CLEM_ASSERT_NOT_NULL(app, "CreateApplication() return nullptr");

	app->init();
	run();
	app->deinit();

	delete app;

	return 0;
}

void Main::run()
{
	CLEM_ASSERT_FALSE(running, "already running");
	running = true;
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

void Main::resume()
{
	paused = false;
}

void Main::mainLoop()
{
	auto previous = getCurrentMillSecond();

	while(running)
	{
		auto current = getCurrentMillSecond();
		auto dt      = static_cast<uint16_t>(current - previous);
		previous     = current;

		updateInput(dt);
		update(dt);

		updateFrameRate(dt);

		while(paused)
		{
			std::this_thread::sleep_for(500ms);
			previous = getCurrentMillSecond();
		}
	}
}

void Main::updateInput(uint16_t dt)
{
	PROFILE_FUNC();

	static uint16_t lag = 0;
	lag += dt;
	if(lag >= msPerInput)
	{
		Keyboard::update();
		Mouse::update();
		lag = 0;
	}
}

void Main::update(uint16_t dt)
{
	PROFILE_FUNC();

	static uint16_t lag = 0;
	lag += dt;
	while(lag >= msPerUpdate)
	{
		registry.update(dt / 1000.0f);
		lag -= msPerUpdate;
	}
}

void Main::updateFrameRate(uint16_t dt)
{
	PROFILE_FUNC();

	// 计算帧速率
	static uint16_t lag = 0, frames = 0;
	lag += dt;
	frames++;
	if(lag >= 1000)
	{
		frameRate = frames;
		frames = lag = 0;
		Window::setTitle(app->getName() + " | " + std::to_string(frameRate) + "FPS");
	}

	// 积分控制. 限制主循环速度, 减少 CPU 占用
	static const auto target   = std::min({msPerInput, msPerUpdate, msPerRender});
	static uint16_t   integral = 0;
	auto              error    = target - dt;
	integral += error > 0 ? 1 : (integral > 0 ? -1 : 0);
	if(error < 0 && integral == 0)
		return;
	std::this_thread::sleep_for(std::chrono::milliseconds(error + integral));
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

uint16_t Main::getFrameRate()
{
	return frameRate;
}

void Main::init()
{
	PROFILE_SESSION_BEGIN("profile.json");

	// 初始化 ECS, 添加默认系统
	registry.addSystem(new PhysicsSystem());
	registry.addSystem(new RenderSystem());
	registry.addSystem(new ScriptSystem());

	// 初始化日志系统
	Logger::create("core");
	Logger::create("audio");
	Logger::create("assert");
	Logger::create("networking");

	// 初始化 I/O
	Audio::init();
	Keyboard::init();
}

void Main::deinit()
{
	Keyboard::deinit();
	Audio::deinit();

	PROFILE_SESSION_END();
}

#ifdef OS_UNIX

void Main::platformInit()
{
}

#	include <sys/time.h>

long Main::getCurrentMillSecond()
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

long Main::getCurrentMillSecond()
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