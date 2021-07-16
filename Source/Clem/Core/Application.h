// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include "Clem/ECS/Registry.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace clem
{

class Scene;

/**
 * @addtogroup Core
 * @{
 */

/**
 * @brief 应用程序.
 * 用户通过继承该类来创建自己的应用程序.
 */
class Application
{
public:
	/**
	 * @brief 获取单例实例.
	 */
	static Application& get();

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

	/**
	 * @brief 设置更新时间周期.
	 */
	void setMsPerUpdate(uint16_t ms);

	/**
	 * @brief 设置渲染时间周期.
	 */
	void setMsPerRender(uint16_t ms);

	/**
	 * @brief 获取帧速率(FPS).
	 */
	uint16_t getFrameRate() const;

	/**
	 * @brief 获取应用名称.
	 */
	const std::string& getName() const;

	virtual void init();
	virtual void deinit();

private:
	void initPlatform();

	void updateInput(uint16_t dt);
	void updateScene(uint16_t dt);
	void renderScene(uint16_t dt);
	void updateFrameRate(uint16_t dt);

	long getCurrentMillSecond() const;

	bool     quit        = true;
	bool     paused      = false;
	uint16_t msPerInput  = 16;
	uint16_t msPerUpdate = 16;
	uint16_t msPerRender = 16;
	uint16_t frameRate   = 0;

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
} // namespace clem
