// Copyright 2021 SMS
// License(Apache-2.0)

// #define SDL_MAIN_HANDLED
// #include "SDL.h"

#include "Application.h"
#include "Clem.h"
#include <clocale>
#include <csignal>

using namespace clem;
using namespace std::chrono_literals;
using std::shared_ptr;
using std::string;
using std::this_thread::sleep_for;

#include "asio.hpp"

int main(int argc, char* argv[])
{
	PROFILE_SESSION_BEGIN("profile.json");
	auto app = clem::CreateApplication();
	Assert::isNotNull(app, "CreateApplication() returns nullptr", CALL_INFO);

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
	Assert::isNotNull(instance, "get the instance before creating the instance", CALL_INFO);
	return *instance;
}

Application::Application(const string& name)
		: name(name)
{
	Assert::isNull(instance, "try to create the application twice", CALL_INFO);
	instance = this;
	PROFILE_FUNC();

	std::setlocale(LC_ALL, "");
	std::signal(SIGINT, onSignal);

	initPlatform();

	Output::get().setSize(Window::getSize()); // 初始化 Output

	Log::init();
	Audio::init();
	Input::init();
}

Application::~Application()
{
	PROFILE_FUNC();

	Input::deinit();
	Audio::deinit();
	Log::deinit();
}

void Application::run()
{
	Assert::isTrue(quit, "call Application::run() when the application is already running", CALL_INFO);
	CLEM_CORE_INFO("main loop started");

	quit          = false;
	long previous = getCurrentMillSecond();

	while(!quit)
	{
		long current = getCurrentMillSecond();
		long dt      = current - previous;
		previous     = current;

		updateInput(dt);
		updateScene(dt);
		renderScene(dt);

		updateFrameRate(dt);

		if(paused)
		{
			while(paused)
				sleep_for(500ms);
			previous = getCurrentMillSecond();
		}
	}

	CLEM_CORE_INFO("main loop stoped");
}

void Application::updateInput(long dt)
{
	static long lag = 0;

	lag += dt;
	if(lag >= msPerInput)
	{
		Input::update();
		lag = 0;
	}
}

void Application::updateScene(long dt)
{
	static long lag   = 0;
	auto&       scene = scenes.back();

	lag += dt;
	while(lag >= msPerUpdate)
	{
		scene->update(msPerUpdate / 1000.0f);
		lag -= msPerUpdate;
	}
}

void Application::renderScene(long dt)
{
	static long lag   = 0;
	auto&       scene = scenes.back();

	lag += dt;
	while(lag >= msPerRender)
	{
		scene->render(dt / 1000.0f);
		lag -= msPerRender;
		frames++;
	}
}

void Application::updateFrameRate(long dt)
{
	static long fpsLag = 0;

	fpsLag += dt;
	if(fpsLag >= 1000)
	{
		frameRate = frames;
		frames = fpsLag = 0;
		Window::setTitle(name + " | " + std::to_string(frameRate) + "FPS");
	}
}

void Application::stop()
{
	Assert::isFalse(quit, "call Application::stop() when the application has stopped", CALL_INFO);
	quit = true;
}

void Application::pause()
{
	Assert::isFalse(paused, "pause when the main loop is already paused", CALL_INFO);
	paused = true;
}

void Application::resume()
{
	Assert::isTrue(paused, "resume when the main loop is not paused", CALL_INFO);
	paused = false;
}

void Application::setMsPerUpdate(long ms)
{
	Assert::isTrue(ms <= 0, "set ms per update non positive is not allowed", CALL_INFO);
	msPerUpdate = ms;
}

void Application::setMsPerRender(long ms)
{
	Assert::isTrue(ms <= 0, "set ms per render non positive is not allowed", CALL_INFO);
	msPerRender = ms;
}

long Application::getFrameRate() const
{
	return frameRate;
}

const string& Application::getName() const
{
	return name;
}

void Application::pushScene(shared_ptr<Scene>& s)
{
	scenes.push_back(s);
}

void Application::popScene()
{
	Assert::isTrue(scenes.size() < 2, "pop a scene when the scenes is empty is not allowed", CALL_INFO);
	scenes.pop_back();
}

void Application::replaceScene(const shared_ptr<Scene>& s)
{
	Assert::isTrue(scenes.empty(), "replace a scene when the scenes is empty is not allowed", CALL_INFO);
	scenes.back() = s;
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
		CLEM_CORE_WARN("signal: external interrupt, usually initiated by the user");
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
	LARGE_INTEGER freq;
	BOOL          ret = QueryPerformanceFrequency(&freq); // TODO: 只需执行一次
	Assert::isTrue(ret != 0, "the installed hardware doesn't supports a high-resolution performance counter", CALL_INFO);

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return (long)(time.QuadPart * 1000 / freq.QuadPart);
}

#endif
} // namespace clem