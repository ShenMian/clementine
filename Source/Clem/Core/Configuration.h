// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Math/Math.h"
#include <filesystem>

namespace clem
{

class Configuration
{
public:
    class Display
    {
    public:
        enum class Mode
        {
            Fullscreen,
            Windowed,
            Borderless
        };

        static Vector2i resolution;
        static Mode     mode;
        static bool     vsync;
    };

    class Controls
    {
    public:
        static Vector2 mouseSensitivity;
    };

    /**
     * @brief 从文件加载配置.
     *
     * @param path 配置文件路径.
     */
    static void load(const std::filesystem::path& path = "config.json");

    /**
     * @brief 将配置写入文件.
     *
     * @param path 配置文件路径.
     */
    static void save(const std::filesystem::path& path = "config.json");
};

} // namespace clem