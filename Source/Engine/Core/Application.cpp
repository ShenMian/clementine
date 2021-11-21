// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Application.h"
#include "Platform.h"

namespace clem
{

Application& Application::get()
{
    static Application instance;
    return instance;
}

const Application::Config& Application::getConfig() const
{
    return config;
}

void Application::setConfig(const Config& newConfig)
{
    if(newConfig.display != config.display)
    {
        window.setSync(newConfig.display.vsync);
        window.setSize(newConfig.display.resolution);
    }

    config = newConfig;
}

Window& Application::getWindow()
{
    return window;
}

constexpr Application::OS Application::getOS() const
{
#ifdef OS_WIN
    return OS::Windows;
#elif OS_LINUX
    return OS::Linux;
#elif OS_MACOS
    return OS::MacOS;
#endif
}

Application::Application()
    : window(config.about.name, config.display.resolution)
{
}

} // namespace clem
