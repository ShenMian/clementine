// Copyright 2021 SMS
// License(Apache-2.0)

#include "Configuration.h"
#include <json.hpp>
#include <fstream>

namespace fs = std::filesystem;
using json   = nlohmann::json;

namespace clem
{

Vector2i Configuration::displayResolution = {1920, 1080};
bool     Configuration::fullscreen        = false;
bool     Configuration::sync              = true;

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

    displayResolution.x = json["displayResolution"]["x"];
    displayResolution.y = json["displayResolution"]["y"];
    fullscreen          = json["fullscreen"];
    sync                = json["sync"];
}

void Configuration::save(const std::filesystem::path& path)
{
    json json;

    json["displayResolution"]["x"] = displayResolution.x;
    json["displayResolution"]["y"] = displayResolution.y;
    json["fullscreen"]             = fullscreen;
    json["sync"]                   = sync;

    std::ofstream file(path);
    json >> file;
    file.close();
}

} // namespace clem