// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "ECS/Registry.h"
#include <cstdint>
#include <filesystem>
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
	 * @brief 获取应用名称.
	 */
    const std::string& getName() const;

    /**
	 * @brief 获取应用资源目录.
	 */
    const std::filesystem::path& getAssetPath();

    virtual void init();
    virtual void deinit();

    /**
	 * @brief 压入场景.
	 */
    // void pushScene(std::shared_ptr<Scene>& scene);

    /**
	 * @brief 弹出场景.
	 */
    // void popScene();

    /**
	 * @brief 替换场景.
	 */
    // void replaceScene(const std::shared_ptr<Scene>& scene);

private:
    const std::string     name;
    std::filesystem::path asset = "../assets";

    // std::vector<std::shared_ptr<Scene>> scenes;

    static Application* instance;
};

Application* CreateApplication();

/**
 * end of Core group
 * @}
 */

} // namespace clem
