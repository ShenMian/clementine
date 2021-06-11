// Copyright 2021 SMS
// License(Apache-2.0)

// #define SDL_MAIN_HANDLED
// #include "SDL.h"

#include "Application.h"
#include "Clem.h"
#include <clocale>
#include <csignal>
#include <map>

using namespace clem;
using namespace std::chrono_literals;
using std::map;
using std::shared_ptr;
using std::string;
using std::string_view;

#include <iostream>

int main(int argc, char* argv[])
{
	PROFILE_SESSION_BEGIN("profile.json");

	auto app = clem::CreateApplication();
	CLEM_ASSERT_NOT_NULL(app, "CreateApplication() returns nullptr");

	app->init();
	app->run();
	app->deinit();

	delete app;

	PROFILE_SESSION_END();
	return 0;
}

namespace clem
{
Application* Application::instance = nullptr;

Application& Application::get()
{
	CLEM_ASSERT_NOT_NULL(instance, "get the instance before creating the instance");
	return *instance;
}

Application::Application(const string& name)
		: name(name)
{
	CLEM_ASSERT_NULL(instance, "try to create the application twice");
	instance = this;
	PROFILE_FUNC();

	std::setlocale(LC_ALL, "");

	std::signal(SIGINT, Application::onSignal);

	initPlatform();

	Output::get().setSize(Window::getVisibleSize());

	Logger::create("core");
	Logger::create("audio");
	Logger::create("assert");
	Logger::create("networking");

	Audio::init();
	Keyboard::init();
}

Application::~Application()
{
	PROFILE_FUNC();

	Keyboard::deinit();
	Audio::deinit();
}

void Application::run()
{
	CLEM_ASSERT_TRUE(quit, "call Application::run() when the application is already running");
	CLEM_LOG_INFO("core", "main loop started");

	quit          = false;
	auto previous = getCurrentMillSecond();

	while(!quit)
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

	CLEM_LOG_INFO("core", "main loop stoped");
}

void Application::updateInput(uint16_t dt)
{
	PROFILE_FUNC();

	static long lag = 0;

	lag += dt;
	if(lag >= msPerInput)
	{
		Keyboard::update();
		Mouse::update();
		// TODO: 清除 inputRecords 中不关注的事件
		lag = 0;
	}
}

void Application::updateScene(uint16_t dt)
{
	PROFILE_FUNC();

	auto&           scene = scenes.back();
	static uint16_t lag   = 0;

	lag += dt;
	while(lag >= msPerUpdate)
	{
		scene->update(msPerUpdate / 1000.0f);
		lag -= msPerUpdate;
	}
}

void Application::renderScene(uint16_t dt)
{
	PROFILE_FUNC();

	auto&           scene = scenes.back();
	static uint16_t lag   = 0;

	lag += dt;
	if(lag >= msPerRender)
	{
		scene->render(dt / 1000.0f);
		lag = 0;
	}
}

void Application::updateFrameRate(uint16_t dt)
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
		Window::setTitle(name + " | " + std::to_string(frameRate) + "FPS");
	}

	// 限制主循环速度, 减少 CPU 占用
	static const auto target   = std::min({msPerInput, msPerUpdate, msPerRender});
	static uint16_t   integral = 0;
	auto              error    = target - dt;
	integral += error > 0 ? 1 : (integral > 0 ? -1 : 0);
	if(error < 0 && integral == 0)
		return;
	std::this_thread::sleep_for(std::chrono::milliseconds(error + integral));
}

void Application::stop()
{
	CLEM_ASSERT_FALSE(quit, "call Application::stop() when the application has stopped");
	quit = true;
}

void Application::pause()
{
	CLEM_ASSERT_FALSE(paused, "pause when the main loop is already paused");
	paused = true;
}

void Application::resume()
{
	CLEM_ASSERT_TRUE(paused, "resume when the main loop is not paused");
	paused = false;
}

void Application::pushScene(shared_ptr<Scene>& s)
{
	scenes.push_back(s);
}

void Application::popScene()
{
	CLEM_ASSERT_TRUE(scenes.size() < 2, "pop a scene when the scenes is empty is not allowed");
	scenes.pop_back();
}

void Application::replaceScene(const shared_ptr<Scene>& s)
{
	CLEM_ASSERT_TRUE(scenes.empty(), "replace a scene when the scenes is empty is not allowed");
	scenes.back() = s;
}

void Application::setMsPerUpdate(uint16_t ms)
{
	msPerUpdate = ms;
}

void Application::setMsPerRender(uint16_t ms)
{
	msPerRender = ms;
}

uint16_t Application::getFrameRate() const
{
	return frameRate;
}

const string& Application::getName() const
{
	return name;
}

void Application::init()
{
}

void Application::deinit()
{
}

void Application::onSignal(int signal)
{
	switch(signal)
	{
	case SIGINT:
		CLEM_LOG_WARN("core", "signal: external interrupt, usually initiated by the user");
		instance->stop();
		break;

	default:
		assert(false);
	}
}

#ifdef OS_UNIX

void Application::initPlatform()
{
}

#	include <sys/time.h>

long Application::getCurrentMillSecond() const
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec * 0.001;
}

#endif

#ifdef OS_WIN

void Application::initPlatform()
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

long Application::getCurrentMillSecond() const
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