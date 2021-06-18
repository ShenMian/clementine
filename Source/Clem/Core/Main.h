// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <vector>
#include <cstdint>

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
	 * @brief ������.
	 */
	static int main(int argc, char* argv[]);

	/**
	 * @brief ������ѭ��.
	 */
	static void run();

	/**
	 * @brief ��ֹ��ѭ��.
	 */
	static void stop();

	/**
	 * @brief ��ͣ��ѭ��.
	 */
	static void pause();

	/**
	 * @brief �ָ���ѭ��.
	 */
	static void resume();

	/**
	 * @brief ��ȡ֡����, ��λ: FPS.
	 */
	static uint16_t getFrameRate();

	static void init();
	static void deinit();

private:
	static bool     running;
	static bool     paused;
	static uint16_t msPerInput;
	static uint16_t msPerUpdate;
	static uint16_t msPerRender;
	static uint16_t frameRate;

	static Application* app;

	static void mainLoop();
	static void parseArgs(int argc, char* argv[]);

	static void updateInput(uint16_t dt);
	static void updateScene(uint16_t dt);
	static void renderScene(uint16_t dt);
	static void updateFrameRate(uint16_t dt);

	static void platformInit();
	static long getCurrentMillSecond();
};

/**
 * end of Core group
 * @}
 */
} // namespace clem
