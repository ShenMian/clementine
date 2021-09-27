// Copyright 2021 SMS
// License(Apache-2.0)

#include "Input.h"
#include "Core/Main.h"
#include "Window/Window.h"
#include <glfw/glfw3.h>

namespace clem
{

bool Input::isPressed(KeyCode code)
{
    auto*      handle = static_cast<GLFWwindow*>(Main::getWindow()->nativeHandle());
    const auto state  = glfwGetKey(handle, static_cast<int32_t>(code));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isPressed(MouseCode code)
{
    auto*      handle = static_cast<GLFWwindow*>(Main::getWindow()->nativeHandle());
    const auto state  = glfwGetMouseButton(handle, static_cast<int32_t>(code));
    return state == GLFW_PRESS;
}

Vector2 Input::getMousePosition()
{
    auto* handle = static_cast<GLFWwindow*>(Main::getWindow()->nativeHandle());
    double mouseX, mouseY;
    int    winX, winY;
    glfwGetWindowPos(handle, &winX, &winY);
    glfwGetCursorPos(handle, &mouseX, &mouseY);
    return {(float)(mouseX - winX), (float)(mouseY - winY)};
}

} // namespace clem