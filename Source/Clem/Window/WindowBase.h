// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Core.h"
#include "UI/UI.h"
#include <filesystem>
#include <functional>
#include <string>
#include <vector>

namespace clem
{

class Layer;

/**
 * @brief 窗口.
 */
class WindowBase
{
public:
    /**
	 * @brief 默认构造函数.
	 */
    WindowBase();

    /**
	 * @brief 默认析构函数.
	 */
    virtual ~WindowBase();

    /**
	 * @brief 更新.
	 *
	 * 轮询事件, 响应窗口事件.
	 */
    virtual void update(Time dt) = 0;

    /**
	 * @brief 设置窗口标题.
	 *
	 * @param title 新窗口标题.
	 */
    virtual void setTitle(const std::string& title) = 0;

    /**
	 * @brief 设置窗口大小.
	 *
	 * @param size 新窗口大小.
	 */
    virtual void setSize(Size2i size) = 0;

    /**
	 * @brief 获取窗口大小.
	 *
	 * @return 当前窗口大小.
	 */
    virtual Size2i getSize() = 0;

    /**
	 * @brief 设置窗口坐标.
	 *
	 * @param pos 新窗口坐标.
	 */
    virtual void setPosition(Size2i pos) = 0;

    /**
	 * @brief 获取窗口坐标.
	 *
	 * @return 当前窗口坐标.
	 */
    virtual Size2i getPosition() = 0;

    /**
	 * @brief 设置窗口可见性.
	 *
	 * @param visible true 为可见, false 为不可见.
	 */
    virtual void setVisible(bool visible) = 0;

    /**
	 * @brief 获取窗口可见性.
	 *
	 * @return true 为可见, false 为不可见.
	 */
    virtual bool isVisible() const = 0;

    /**
	 * @brief 设置是否开启垂直同步.
	 *
	 * @param enable true 为开启, false 为关闭.
	 */
    virtual void setSync(bool enable) = 0;

    /**
	 * @brief 设置窗口图标.
	 *
	 * @param path 图标文件路径.
	 */
    virtual void setIcon(const std::filesystem::path& path) = 0;

    virtual void* nativeHandle() const = 0;

    void add(ui::Layer* layer);

    void remove(ui::Layer* layer);

    static void init();
    static void deinit();

    std::function<void(Size2i)>         onResize;
    std::function<void(double, double)> onScroll;
    std::function<void(int, int)>       onKey;
    std::function<void(double, double)> onMouseMove;
    std::function<void(bool)>           onFocus;
    std::function<void()>               onClose;

protected:
    std::vector<ui::Layer*> layers;

private:
    static bool initialized;
};

} // namespace clem