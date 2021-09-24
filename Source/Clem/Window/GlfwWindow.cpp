// Copyright 2021 SMS
// License(Apache-2.0)

#include "GlfwWindow.h"
#include "Components/Components.h"
#include "Events/Events.h"
#include "Platform.h"
#include "Profiler.h"
#include "Rendering/Rendering.h"
#include "UI/UI.h"
#include <cassert>
#include <cstdio>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb/stb_image.h>

namespace fs = std::filesystem;

using std::string;

namespace clem
{

static Vector3 move;

GlfwWindow::GlfwWindow(const std::string& title, Size2i size)
{
    PROFILE_FUNC();

    auto       monitor   = glfwGetPrimaryMonitor();
    const auto videoMode = glfwGetVideoMode(monitor);

    bool fullscreen = false;
    if(fullscreen)
        handle = glfwCreateWindow(videoMode->width, videoMode->height, title.c_str(), monitor, nullptr);
    else
        handle = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(handle);

    auto success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    Assert::isTrue(success, "can't load OpenGL API");

    glfwSetWindowUserPointer(handle, static_cast<void*>(this));

    glfwSetErrorCallback([](int error, const char* desc)
                         { Assert::isTrue(false, desc); });

    glfwSetWindowSizeCallback(handle, [](GLFWwindow* native, int width, int height)
                              {
                                  const auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
                                  Renderer::get()->setViewport(0, 0, width, height);
                                  if(win->onResize)
                                      win->onResize(Size2(width, height));
                              });

    glfwSetWindowCloseCallback(handle, [](GLFWwindow* native)
                               {
                                   const auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
                                   if(win->onClose)
                                       win->onClose();
                               });

    glfwSetScrollCallback(handle, [](GLFWwindow* native, double xOffset, double yOffset)
                          {
                              const auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
                              if(win->onScroll)
                                  win->onScroll(xOffset, yOffset);
                          });

    glfwSetKeyCallback(handle, [](GLFWwindow* native, int key, int scancode, int action, int mods)
                       {
                           const auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
                           if(win->onKey)
                               win->onKey(action, key);
                           // EventDispatcher::get().dispatch(KeyEvent(key, action == GLFW_PRESS || action == GLFW_REPEAT, action == GLFW_REPEAT));
                       });

    glfwSetCursorPosCallback(handle, [](GLFWwindow* native, double x, double y)
                             {
                                 const auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
                                 if(win->onMouseMove)
                                     win->onMouseMove(x, y);
                             });

    glfwSetMouseButtonCallback(handle, nullptr);

    glfwSetWindowFocusCallback(handle, [](GLFWwindow* window, int focused)
                               {
                                   static uint16_t rate = Main::getRenderRate();
                                   if(focused)
                                       Main::setRenderRate(rate);
                                   else
                                   {
                                       rate = Main::getRenderRate();
                                       Main::setRenderRate(5);
                                   }
                               });

    // glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 开启 MASS 抗锯齿
    // glfwWindowHint(GLFW_SAMPLES, 2);
    // glEnable(GL_MULTISAMPLE);

    UI::windowInit(this);
}

GlfwWindow::~GlfwWindow()
{
    PROFILE_FUNC();

    UI::windowDeinit();
    glfwMakeContextCurrent(handle);
    glfwDestroyWindow(handle);
}

void GlfwWindow::update(Time dt)
{
    PROFILE_FUNC();

    auto renderer = Renderer::get();

    renderer->beginFrame();

    UI::beginFrame();
    for(auto layer : layers)
        layer->update(dt);
    UI::endFrame();

    renderer->endFrame();

    glfwSwapBuffers(handle);
    glfwPollEvents();
}

void GlfwWindow::setTitle(const string& title)
{
    glfwSetWindowTitle(handle, title.c_str());
}

void GlfwWindow::setSize(Size2i size)
{
    glfwSetWindowSize(handle, size.x, size.y);
}

Size2i GlfwWindow::getSize()
{
    int x, y;
    glfwGetWindowSize(handle, &x, &y);
    return {x, y};
}

void GlfwWindow::setPosition(Size2i size)
{
    glfwSetWindowPos(handle, size.x, size.y);
}

Size2i GlfwWindow::getPosition()
{
    Size2i size;
    glfwGetWindowPos(handle, &size.x, &size.y);
    return size;
}

void GlfwWindow::setVisible(bool visible)
{
    if(visible)
        glfwShowWindow(handle);
    else
        glfwHideWindow(handle);
}

bool GlfwWindow::isVisible() const
{
    return glfwGetWindowAttrib(handle, GLFW_VISIBLE);
}

void GlfwWindow::setSync(bool enable)
{
    if(enable)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

void GlfwWindow::setIcon(const fs::path& path)
{
    Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", path.string()));

    GLFWimage image;
    int       channels;
    image.pixels = stbi_load(path.string().c_str(), &image.width, &image.height, &channels, 0);
    Assert::isTrue(image.pixels != nullptr, std::format("can't load from file: '{}'", path.string()));

    glfwSetWindowIcon(handle, 1, &image);

    stbi_image_free(image.pixels);
}

void* GlfwWindow::nativeHandle() const
{
    return handle;
}

void GlfwWindow::init()
{
    PROFILE_FUNC();

    auto success = glfwInit();
    Assert::isTrue(success, "GLFW init failed");
}

void GlfwWindow::deinit()
{
    PROFILE_FUNC();
    glfwTerminate();
}

/*
vk::SurfaceKHR GlfwWindow::getWindowSurface(const vk::Instance& vkInstance) const
{
	VkSurfaceKHR surface;
	auto ret = static_cast<vk::Result>(glfwCreateWindowSurface((VkInstance)vkInstance, handle, nullptr, &surface));
	return surface;
}
*/

} // namespace clem