// Copyright 2021 SMS
// License(Apache-2.0)

// #define SDL_MAIN_HANDLED
// #include "SDL.h"

#include "Application.h"
#include "Profiler.h"
#include <map>
#include <string>

using namespace clem;
using namespace std::chrono_literals;
using std::map;
using std::string;
using std::string_view;

namespace clem
{
Application* Application::instance = nullptr;

Application& Application::get()
{
	Assert::isTrue(instance != nullptr, "get the instance before creating the instance");
	return *instance;
}

Application::Application(const string& name)
		: name(name)
{
	Assert::isTrue(instance == nullptr, "try to create the application twice");
	instance = this;
	PROFILE_FUNC();
}

Application::~Application()
{
	PROFILE_FUNC();
}

/*
void Application::pushScene(shared_ptr<Scene>& s)
{
	scenes.push_back(s);
}

void Application::popScene()
{
	Assert::isTrue(scenes.size() < 2, "pop a scene when the scenes is empty is not allowed");
	scenes.pop_back();
}

void Application::replaceScene(const shared_ptr<Scene>& s)
{
	Assert::isTrue(scenes.empty(), "replace a scene when the scenes is empty is not allowed");
	scenes.back() = s;
}
*/

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

} // namespace clem