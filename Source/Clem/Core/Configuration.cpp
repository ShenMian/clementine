// Copyright 2021 SMS
// License(Apache-2.0)

#include "Configuration.h"
#include "Assert.hpp"
#include <fstream>
#include <json.hpp>

namespace fs = std::filesystem;
using json   = nlohmann::json;

namespace clem
{

Vector2i                     Configuration::Display::resolution        = {1920, 1080};
Configuration::Display::Mode Configuration::Display::mode              = Mode::Windowed;
bool                         Configuration::Display::vsync             = true;
Vector2                      Configuration::Controls::mouseSensitivity = {0.05, 0.05};

void Configuration::load(const std::filesystem::path& path)
{
    if(!fs::exists(path))
    {
        save();
        return;
    }

    json json;

    std::ifstream file(path);
    file >> json;
    file.close();

    try
    {
        Display::resolution.x = json["display"]["resolution"]["x"];
        Display::resolution.y = json["display"]["resolution"]["y"];
        Display::mode         = json["display"]["mode"];
        Display::vsync        = json["display"]["vsync"];

        Controls::mouseSensitivity.x = json["controls"]["mouse_sensitivity"]["x"];
        Controls::mouseSensitivity.y = json["controls"]["mouse_sensitivity"]["y"];
    }
    catch(nlohmann::detail::exception& e)
    {
        Assert::isTrue(false, e.what());
    }
}

void Configuration::save(const std::filesystem::path& path)
{
    json json;

    json["display"]["resolution"]["x"] = Display::resolution.x;
    json["display"]["resolution"]["y"] = Display::resolution.y;
    json["display"]["mode"]            = Display::mode;
    json["display"]["vsync"]           = Display::vsync;

    json["controls"]["mouse_sensitivity"]["x"] = Controls::mouseSensitivity.x;
    json["controls"]["mouse_sensitivity"]["y"] = Controls::mouseSensitivity.y;

    std::ofstream file(path);
    json >> file;
    file.close();
}

} // namespace clem