-- Copyright 2021 SMS
-- License(Apache-2.0)

include "thirdparty/premake/solution_items.lua"

workspace "Clementine"
  architecture "x86_64"
  startproject "Examples"
  configurations {"Debug", "Release"}
  flags "MultiProcessorCompile"

  solution_items {
    ".clang-format",
    "CMakeLists.txt",
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
thirdparty["entt"] = "%{wks.location}/thirdparty/entt"
thirdparty["spdlog"] = "%{wks.location}/thirdparty/spdlog"
thirdparty["yaml_cpp"] = "%{wks.location}/thirdparty/yaml-cpp"
thirdparty["sdl"] = "%{wks.location}/thirdparty/sdl"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Thirdparty"
  include "thirdparty/sdl"
  include "thirdparty/yaml-cpp"
group ""

include "src"
include "examples"
