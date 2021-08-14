// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>

int main(int argc, char* argv[]);

namespace clem
{
/**
 * @addtogroup Core
 * @{
 */

class Application;
class WindowBase;
class Registry;

extern Application* CreateApplication();

class Main
{
public:
    /**
	 * @brief 主函数.
	 */
    static int main(int argc, char* argv[]);

    /**
	 * @brief 启动主循环.
	 */
    static void run();

    /**
	 * @brief 终止主循环.
	 */
    static void stop();

    /**
	 * @brief 暂停主循环.
	 */
    static void pause();

    /**
	 * @brief 恢复主循环.
	 */
    static void resume();

    /**
	 * @brief 获取帧速率, 单位: FPS.
	 */
    static uint16_t getFrameRate();

    static WindowBase* getWindow();

    /**
     * @brief 设置输入设备轮询帧率. (未来将移除, 放在 BaseWindow::update 中)
     */
    static void     setInputRate(uint16_t rate);
    static uint16_t getInputRate();
    static void     setUpdateRate(uint16_t rate);
    static uint16_t getUpdateRate();

    /**
     * @brief 设置目标渲染帧率, 单位: Hz.
     * 
     * @param rate 目标渲染帧率.
     */
    static void     setRenderRate(uint16_t rate);

    /**
     * @brief 获取目标渲染帧率, 单位: Hz.
     */
    static uint16_t getRenderRate();

    static void init();
    static void deinit();

    static Registry registry;

private:
    static bool     running;
    static bool     paused;
    static uint16_t inputRate;
    static uint16_t updateRate;
    static uint16_t renderRate;
    static uint16_t frameRate;

    static Application* app;
    static WindowBase*  window;

    static void mainLoop();
    static void parseArgs(int argc, char* argv[]);

    static void updateInput(uint16_t dt);
    static void update(uint16_t dt);
    static void render(uint16_t dt);
    static void updateFrameRate(uint16_t dt);

    static long getCurrentMillSecond();

    static void onSignal(int signal);
};

/**
 * end of Core group
 * @}
 */
} // namespace clem
