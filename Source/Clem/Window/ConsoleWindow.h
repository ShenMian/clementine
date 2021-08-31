// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "WindowBase.h"

namespace clem
{

/**
 * @brief 终端窗口.
 */
class ConsoleWindow : public WindowBase
{
public:
    /**
	  * @brief 构造函数.
	  *
	  * @param title 窗口标题.
	  * @param size 可绘制区域大小, 不一定等于窗口大小.
	  */
    ConsoleWindow(const std::string& title, Size2i size);

    void update(Time dt) override;

    /**
	  * @warning 此函数性能不稳定, 可能造成超高延迟, 不应该频繁调用.
 	  */
    void setTitle(const std::string& title) override;

    /**
	  * @warning 不影响终端窗口大小.
	  */
    void setSize(Size2i size) override;

    /**
 	  * @warning 不代表终端窗口大小.
 	  */
    Size2i getSize() override;

    /**
	  * @warning 终端窗口不支持.
	  */
    void setPosition(Size2i pos) override;

    /**
	  * @warning 终端窗口不支持.
	  */
    Size2i getPosition() override;

    /**
	  * @warning 终端窗口不支持.
	  */
    void setVisible(bool visible) override;

    /**
	  * @warning 终端窗口不支持.
	  *
	  * @return true
	  */
    bool isVisible() const override;

    /**
	  * @warning 终端窗口不支持.
	  */
    void setSync(bool enable) override;

    /**
	  * @warning 终端窗口不支持.
	  */
    void setIcon(const std::filesystem::path& path) override;

    /**
	  * @warning 终端窗口不支持.
		*
		* @return nullptr
	  */
    void* nativeHandle() const override;

    static void init();
    static void deinit();

private:
    Size2i size;
};

} // namespace clem