// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_CORE_APPLICATION_H_
#define CLEM_CORE_APPLICATION_H_

#include "Clem/Math/Vec2.h"
#include <memory>
#include <string>
#include <thread>
#include <vector>

class Scene;

/**
 * @addtogroup Core
 * @{
 */

class Application
{
public:
	static Application& getInstance();

	/**
	 * @brief 构造函数.
	 */
	Application(const std::string& name = "Clementine");

	/**
	 * @brief 析构函数.
	 */
	virtual ~Application();

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
	 * @brief 设置更新时间周期.
	 */
	void setMsPerUpdate(long ms);

	/**
	 * @brief 设置渲染时间周期.
	 */
	void setMsPerRender(long ms);

	/**
	 * @brief 获取帧速率(FPS).
	 */
	long getFrameRate() const;

	/**
	 * @brief 获取应用名称.
	 */
	const std::string& getName() const;

	/**
	 * @brief 压入场景.
	 */
	void pushScene(std::shared_ptr<Scene>& scene);

	/**
	 * @brief 弹出场景.
	 */
	void popScene();

	/**
	 * @brief 替换场景.
	 */
	void replaceScene(const std::shared_ptr<Scene>& scene);

private:
	void initialize();

	void updateInput();
	void updateScene(long dt);
	void renderScene(long dt);
	void updateFrameRate(long dt);
	long getCurrentMillSecond() const;

	bool quit        = false;
	bool paused      = false;

	long msPerUpdate = 16;
	long msPerRender = 16;

	long frameRate   = 0;
	long frames      = 0;

	std::thread inputThread;

	std::vector<std::shared_ptr<Scene>> scenes;

	const std::string name;

	static void         onSignal(int signal);
	static Application* instance;
};

Application* CreateApplication();

/**
 * end of Core group
 * @}
 */

#endif // !CLEM_CORE_APPLICATION_H_
