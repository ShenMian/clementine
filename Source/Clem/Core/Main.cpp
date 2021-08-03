// Copyright 2021 SMS
// License(Apache-2.0)

#include "Main.h"
#include "Application.h"

#include "Assert.hpp"
#include "Audio/Audio.h"
#include "Components/ScriptSystem.h"
#include "Core/Core.h"
#include "ECS/Registry.h"
#include "Logger.h"
#include "Physics/Physics.h"
#include "Profiler.h"
#include "Rendering/Rendering.h"
#include "Time.h"
#include "Window/Window.h"
#include <csignal>
#include <map>
#include <string>

using namespace std::chrono_literals;
using clem::Main;

// #pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

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
bool         Main::running    = false;
bool         Main::paused     = false;
uint16_t     Main::inputRate  = 250; // 125, 250, 500, 1000 TODO: 根据外设回报率自动调整
uint16_t     Main::updateRate = 144;
uint16_t     Main::renderRate = 144; // 60, 144, 165, 240 TODO: 根据显示器刷新率自动调整
uint16_t     Main::frameRate  = 0;
Application* Main::app        = nullptr;
WindowBase*  Main::window;

int Main::main(int argc, char* argv[])
{
    parseArgs(argc, argv);

    app = CreateApplication();
    Assert::isTrue(app != nullptr, "CreateApplication() return nullptr");

    app->init();
    run();
    app->deinit();

    delete app;

    return 0;
}

void Main::run()
{
    Assert::isFalse(running, "already running");
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

        if(dt)
        {
            updateInput(dt);
            update(dt);
            render(dt);
            updateFrameRate(dt);
        }

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
    if(lag >= 1000 / inputRate)
    {
        // Keyboard::update();
        // Mouse::update();
        lag -= 1000 / inputRate;
    }
}

void Main::update(uint16_t dt)
{
    PROFILE_FUNC();

    static uint16_t lag = 0;
    lag += dt;
    while(lag >= 1000 / updateRate)
    {
        registry.update(milliseconds(dt));
        lag -= 1000 / updateRate;
    }
}

void Main::render(uint16_t dt)
{
    PROFILE_FUNC();

    static uint16_t lag = 0;
    lag += dt;
    if(lag >= 1000 / renderRate)
    {
        window->update(milliseconds(dt));
        frames++;
        lag -= 1000 / renderRate;
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
    const auto target = static_cast<uint16_t>(
        1000 / std::max({inputRate, updateRate, renderRate}));
    static int integral = 0;
    auto       error    = target - dt;
    if(error)
    {
        integral += error > 0 ? std::abs(error) : -std::abs(error);
        if(error + integral <= 0)
            return;
        std::this_thread::sleep_for(std::chrono::milliseconds(error + integral));
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

uint16_t Main::getFrameRate()
{
    return frameRate;
}

WindowBase* Main::getWindow()
{
    return window;
}

void Main::setInputRate(uint16_t rate)
{
    assert(rate != 0);
    inputRate = rate;
}

uint16_t Main::getInputRate()
{
    return inputRate;
}

void Main::setUpdateRate(uint16_t rate)
{
    assert(rate != 0);
    updateRate = rate;
}

uint16_t Main::getUpdateRate()
{
    return updateRate;
}

void Main::setRenderRate(uint16_t rate)
{
    assert(rate != 0);
    renderRate = rate;
}

uint16_t Main::getRenderRate()
{
    return renderRate;
}

void Main::init()
{
    PROFILE_SESSION_BEGIN("profile.json");

    // 初始化日志系统
    Logger::create("core");
    Logger::create("audio");
    Logger::create("assert");
    Logger::create("render");
    Logger::create("network");

    // 初始化窗口
    WindowBase::init();
    // window = new ConsoleWindow("Clementine", {80, 25});
    window          = new GlfwWindow("Clementine", {1160, 720});
    window->onClose = []() { Main::stop(); };

    // 初始化渲染器
    // Renderer::setAPI(Renderer::API::Vulkan);
    Renderer::get()->init();

    // 初始化 ECS, 添加默认系统
    registry.addSystem(new PhysicsSystem());
    registry.addSystem(new ScriptSystem());

    registry.addSystem(new RenderSystem());

    // 初始化 I/O
    Audio::init();
    Keyboard::init();

    // std::setlocale(LC_ALL, "");
    std::signal(SIGINT, Main::onSignal);
}

void Main::deinit()
{
    Keyboard::deinit();
    Audio::deinit();

    Renderer::get()->deinit();

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

#    include <sys/time.h>

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
    Assert::isTrue(ret != 0, "the installed hardware doesn't supports a high-resolution performance counter");

    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return (long)(time.QuadPart * 1000 / freq.QuadPart);
}

#endif

} // namespace clem