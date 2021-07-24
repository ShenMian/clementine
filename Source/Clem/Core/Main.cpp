// Copyright 2021 SMS
// License(Apache-2.0)

#include "Main.h"
#include "Application.h"

#include "Clem/Assert.h"
#include "Clem/Audio/Audio.h"
#include "Clem/Components/ScriptSystem.h"
#include "Clem/Core/Core.h"
#include "Clem/ECS/Registry.h"
#include "Clem/Logger.h"
#include "Clem/Physics/Physics.h"
#include "Clem/Profiler.h"
#include "Clem/Rendering/Rendering.h"
#include "Clem/Window/Window.h"
#include <csignal>
#include <map>
#include <string>

using namespace std::chrono_literals;
using clem::Main;

int main(int argc, char* argv[])
{
	Main::init();
	auto ret = Main::main(argc, argv);
	Main::deinit();
	return ret;
}

namespace clem
{

static uint16_t frames = 0;

Registry     Main::registry;
bool         Main::running     = false;
bool         Main::paused      = false;
uint16_t     Main::msPerInput  = 1000 / 144;
uint16_t     Main::msPerUpdate = 1000 / 144;
uint16_t     Main::msPerRender = 1000 / 144;
uint16_t     Main::frameRate   = 0;
Application* Main::app         = nullptr;
WindowBase*  Main::window;

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
		render(dt);
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
		registry.update(milliseconds(dt));
		lag -= msPerUpdate;
	}
}

void Main::render(uint16_t dt)
{
	PROFILE_FUNC();
	
	static uint16_t lag = 0;
	lag += dt;
	if(lag >= msPerRender)
	{
		window->update(milliseconds(dt));
		frames++;
		lag = 0;
	}
}

void Main::updateFrameRate(uint16_t dt)
{
	PROFILE_FUNC();

	// 计算帧速率
	static uint16_t lag = 0;
	lag += dt;
	if(lag >= 1000)
	{
		frameRate = frames;
		frames = lag = 0;
		window->setTitle(app->getName() + " | " + std::to_string(frameRate) + "FPS");
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

WindowBase* Main::getMainWindow()
{
	return window;
}

void Main::init()
{
	PROFILE_SESSION_BEGIN("profile.json");

	// std::setlocale(LC_ALL, "");
	std::signal(SIGINT, Main::onSignal);

	// 初始化日志系统
	Logger::create("core");
	Logger::create("audio");
	Logger::create("assert");
	Logger::create("networking");

	// 初始化 ECS, 添加默认系统
	registry.addSystem(new PhysicsSystem());
	registry.addSystem(new RenderSystem());
	registry.addSystem(new ScriptSystem());

	// 初始化窗口
	WindowBase::init();
	// window = new ConsoleWindow("Clementine", {80, 25});
	window          = new GlfwWindow("Clementine", {1920 / 2, 1080 / 2});
	window->onClose = []() { Main::running = false; };

	// 初始化 I/O
	Audio::init();
	Keyboard::init();
}

void Main::deinit()
{
	Keyboard::deinit();
	Audio::deinit();
	window->deinit();

	PROFILE_SESSION_END();
}

void Main::onSignal(int signal)
{
	switch(signal)
	{
	case SIGINT:
		CLEM_LOG_WARN("core", "signal: external interrupt, usually initiated by the user");
		stop();
		break;

	default:
		assert(false);
	}
}

#ifdef OS_UNIX

#	include <sys/time.h>

long Main::getCurrentMillSecond()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec * 0.001;
}

#endif

#ifdef OS_WIN

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