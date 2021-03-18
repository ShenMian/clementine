// Copyright 2021 SMS
// License(Apache-2.0)

#include "Application.h"
#include "Clem/Log.h"
#include "Clem/Platform.h"
#include "Clem/Profiler.h"
#include "Clem/Scene.h"
#include "Clem/Window.h"
#include <csignal>

using std::shared_ptr;
using std::string;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

int main(int argc, char* argv[])
{
	Log::init();
	PROFILE_SESSION_BEGIN("profile.json");

	auto app = CreateApplication();
	app->run();
	delete app;

	PROFILE_SESSION_END();
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
		assert(false);
	}
	instance = this;
	PROFILE_FUNC();

	std::signal(SIGINT, onSignal);

	initialize();
}

Application::~Application()
{
}

void Application::run()
{
	CLEM_CORE_INFO("main loop started");

	running       = true;
	long previous = getCurrentMillSecond();

	while(running)
	{
		long current = getCurrentMillSecond();
		long dt      = current - previous;
		previous     = current;

		update(dt);
		render(dt);

		if(paused)
		{
			while(paused)
				sleep_for(milliseconds(500));
			previous = getCurrentMillSecond();
		}
	}

	CLEM_CORE_INFO("main loop stoped");
}

void Application::stop()
{
	running = false;
}

void Application::pause()
{
	if(paused)
		CLEM_CORE_WARN("pause when the main loop is already paused");
	paused = true;
}

void Application::resume()
{
	if(!paused)
		CLEM_CORE_WARN("resume when the main loop is not paused");
	paused = false;
}

const std::string& Application::getName() const
{
	return name;
}

void Application::setMsPerUpdate(long ms)
{
	if(ms <= 0)
	{
		CLEM_CORE_CRITICAL("set ms per update non positive is not allowed");
		assert(false);
	}
	msPerUpdate = ms;
}

void Application::setMsPerRender(long ms)
{
	if(ms <= 0)
	{
		CLEM_CORE_CRITICAL("set ms per render non positive is not allowed");
		assert(false);
	}
	msPerRender = ms;
}

void Application::update(long dt)
{
	auto& scene = scenes.back();

	static long lag = 0;
	lag += dt;
	while(lag >= msPerUpdate)
	{
		PROFILE_FUNC();
		scene->update(msPerUpdate / 1000.0f);
		lag -= msPerUpdate;
	}
}

void Application::render(long dt)
{
	auto& scene = scenes.back();

	static long fpsLag = 0, frames = 0;
	fpsLag += dt;
	if(fpsLag >= 1000)
	{
		framesPerSecond = frames;
		frames = fpsLag = 0;
		Window::setTitle(name + " | " + std::to_string(getFramesPerSecond()) + "FPS");
	}

	static long lag = 0;
	lag += dt;
	while(lag >= msPerRender)
	{
		PROFILE_FUNC();
		scene->render(dt / 1000.0f);
		lag -= msPerRender;
		frames++;
	}
}

long Application::getFramesPerSecond() const
{
	return framesPerSecond;
}

void Application::pushScene(shared_ptr<Scene>& s)
{
	scenes.push_back(s);
}

void Application::popScene()
{
	if(scenes.empty())
	{
		CLEM_CORE_CRITICAL("pop a scene when the scenes is empty is not allowed");
		assert(false);
	}
	scenes.pop_back();
}

void Application::replaceScene(std::shared_ptr<Scene>& s)
{
	if(scenes.empty())
	{
		CLEM_CORE_CRITICAL("replace a scene when the scenes is empty is not allowed");
		assert(false);
	}
	scenes.back() = s;
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

void Application::initialize()
{
}

long Application::getCurrentMillSecond() const
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec * 0.001;
}

#endif

#ifdef OS_WIN

void Application::initialize()
{
	// 开启 VT100 模式
	const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD      mode;
	if(!GetConsoleMode(hOut, &mode))
		assert(false);
	if(!SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
		assert(false);
}

long Application::getCurrentMillSecond() const
{
	LARGE_INTEGER freq;
	BOOL          ret = QueryPerformanceFrequency(&freq);
	assert(ret != 0);
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time.QuadPart * 1000 / freq.QuadPart;
}

#endif
