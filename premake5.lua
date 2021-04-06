-- Copyright 2021 SMS
-- License(Apache-2.0)

include "thirdparty/premake/solution_items.lua"

workspace "Clementine"
  architecture "x86_64"
  startproject "Sort"
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
thirdparty["sdl"] = "%{wks.location}/thirdparty/sdl"
thirdparty["entt"] = "%{wks.location}/thirdparty/entt"
thirdparty["spdlog"] = "%{wks.location}/thirdparty/spdlog"
thirdparty["openal"] = "%{wks.location}/thirdparty/openal"
thirdparty["yaml_cpp"] = "%{wks.location}/thirdparty/yaml-cpp"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

include "src"

group "Examples"
  include "examples/pong"
  include "examples/minesweeper"
  include "examples/sort"
  include "examples/gamepad"
  include "examples/2048"
  include "examples/sound"
group ""

group "Thirdparty"
  include "thirdparty/yaml-cpp"
group ""
