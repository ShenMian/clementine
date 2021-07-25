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

	static WindowBase* getWindow();

	static void     setInputRate(uint16_t rate);
	static uint16_t getInputRate();
	static void     setUpdateRate(uint16_t rate);
	static uint16_t getUpdateRate();
	static void     setRenderRate(uint16_t rate);
	static uint16_t getRenderRate();

	static Registry registry;

	static void init();
	static void deinit();

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
