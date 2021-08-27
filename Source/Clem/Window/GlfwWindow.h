// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "WindowBase.h"
#include <memory>
#include <string_view>
#include <vector>

struct GLFWwindow;

namespace vk
{
class Instance;
class SurfaceKHR;
}; // namespace vk

namespace clem
{

class Shader;
class VertexBuffer;
class IndexBuffer;

/**
 * @brief 窗口.
 */
class GlfwWindow : public WindowBase
{
public:
    /**
	 * @brief 构造函数.
	 *
	 * @param title 窗口标题.
	 * @param size 窗口大小.
	 */
    GlfwWindow(const std::string& title, Size2i size);

    /**
	 * @brief 默认析构函数.
	 */
    ~GlfwWindow();

    void   update(Time dt) override;
    void   setTitle(const std::string& title) override;
    void   setSize(Size2 size) override;
    Size2  getSize() override;
    void   setPosition(Size2i pos) override;
    Size2i getPosition() override;
    void   setVisible(bool visible) override;
    bool   isVisible() const override;
    void   setSync(bool enable) override;
    void   setIcon(const std::filesystem::path& path) override;
    void*  nativeHandle() const override;

    std::vector<std::string_view> getRequiredInstanceExtensions() const;
    vk::SurfaceKHR                getWindowSurface(const vk::Instance& vkInstance) const;

    static void init();
    static void deinit();

private:
    GLFWwindow* handle;
};

} // namespace clem