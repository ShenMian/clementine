// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <vector>

int main(int argc, char* argv[]);

namespace clem
{
/**
 * @addtogroup Core
 * @{
 */

class Application;

extern Application* CreateApplication();

class Main
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	Main();

	/**
	 * @brief 默认析构函数.
	 */
	~Main();

	/**
	 * @brief 主函数.
	 */
	int main(int argc, char* argv[]);

	/**
	 * @brief 启动主循环.
	 */
	void run();

	/**
	 * @brief 终止主循环.
	 */
	void stop();

	/**
	 * @brief 暂停主循环.
	 */
	void pause();

	/**
	 * @brief 恢复主循环.
	 */
	void resume();

	/**
	 * @brief 获取帧速率, 单位: FPS.
	 */
	uint16_t getFrameRate() const;

private:
	bool     running     = true;
	bool     paused      = false;
	uint16_t msPerInput  = 16;
	uint16_t msPerUpdate = 16;
	uint16_t msPerRender = 16;
	uint16_t frameRate   = 0;

	Application* app = nullptr;

	void init();
	void deinit();

	void mainLoop();
	void parseArgs(int argc, char* argv[]);

	void updateInput(uint16_t dt);
	void updateScene(uint16_t dt);
	void renderScene(uint16_t dt);
	void updateFrameRate(uint16_t dt);

	void platformInit();
	long getCurrentMillSecond() const;
};

/**
 * end of Core group
 * @}
 */
} // namespace clem
