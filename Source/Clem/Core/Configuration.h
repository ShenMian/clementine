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
     * @brief ���ļ���������.
     *
     * @param path �����ļ�·��.
     */
    static void load(const std::filesystem::path& path = "config.json");

    /**
     * @brief ������д���ļ�.
     *
     * @param path �����ļ�·��.
     */
    static void save(const std::filesystem::path& path = "config.json");
};

} // namespace clem