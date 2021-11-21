// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <Math/Vector2.hpp>
#include <Core/Window.h>
#include <string>
#include <filesystem>

namespace clem
{

class Application
{
public:
    struct Config
    {
        struct About
        {
            std::string name;
            std::string version;
            std::string author;
            std::string description;
        };

        struct Display
        {
            bool     vsync = true;
            Vector2i resolution;

            bool operator==(const Display&) const = default;
        };

        About                 about;
        Display               display;
        std::filesystem::path asset;
    };

    enum class OS;

    static Application& get();

    const Config& getConfig() const;

    void setConfig(const Config& config);

    Window& getWindow();

    constexpr OS getOS() const;

private:
    Application();
    
    Config config;
    Window window;
};

enum class Application::OS
{
    Windows,
    Linux,
    MacOS
};

} // namespace clem