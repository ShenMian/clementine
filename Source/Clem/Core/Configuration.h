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
    static Vector2i displayResolution;
    static bool     fullscreen;
    static bool     sync;

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