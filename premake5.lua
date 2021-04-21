-- Copyright 2021 SMS
-- License(Apache-2.0)

include "thirdparty/premake/solution_items.lua"

workspace "Clementine"
  architecture "x86_64"
  startproject "Pong"
  configurations {"Debug", "Release"}
  flags "MultiProcessorCompile"

  solution_items {
    ".clang-format",
    "CMakeLists.txt",
    "README.md",
    "README-cn.md",
    "premake5.lua"}

  filter "configurations:Debug"
    defines "DEBUG"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    defines "NDEBUG"
    runtime "Release"
    optimize "on"

thirdparty = {}
thirdparty["sdl"] = "%{wks.location}/Thirdparty/sdl"
thirdparty["asio"] = "%{wks.location}/Thirdparty/asio"
thirdparty["entt"] = "%{wks.location}/Thirdparty/entt"
thirdparty["spdlog"] = "%{wks.location}/Thirdparty/spdlog"
thirdparty["openal"] = "%{wks.location}/Thirdparty/openal"
thirdparty["yaml_cpp"] = "%{wks.location}/Thirdparty/yaml-cpp"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

include "Source"

group "Examples"
  include "Examples/2048"
  include "Examples/gobang"
  include "Examples/gamepad"
  include "Examples/minesweeper"
  include "Examples/pong"
  include "Examples/sort"
  include "Examples/sound"
group ""

group "Thirdparty"
  include "Thirdparty/yaml-cpp"
group ""
