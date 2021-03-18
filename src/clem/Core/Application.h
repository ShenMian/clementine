// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_CORE_APPLICATION_H_
#define CLEM_CORE_APPLICATION_H_

#include "Clem/Math.h"
#include <memory>
#include <string>
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
	 * @brief 获取应用名称.
	 */
	const std::string& getName() const;

	/**
	 * @brief 设置更新时间周期.
	 */
	void setMsPerUpdate(long ms);

	/**
	 * @brief 设置渲染时间周期.
	 */
	void setMsPerRender(long ms);

	/**
	 * @brief 获取每秒帧数(FPS).
	 */
	long getFramesPerSecond() const;

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
	void replaceScene(std::shared_ptr<Scene>& scene);

private:
	void initialize();
	void update(long dt);
	void render(long dt);
	long getCurrentMillSecond() const;

	bool                                running         = false;
	bool                                paused          = false;
	long                                msPerUpdate     = 16;
	long                                msPerRender     = 16;
	long                                framesPerSecond = 0;
	const std::string                   name;
	std::vector<std::shared_ptr<Scene>> scenes;

	static void         onSignal(int signal);
	static Application* instance;
};

Application* CreateApplication();

/**
 * end of Core group
 * @}
 */

#endif // !CLEM_CORE_APPLICATION_H_
