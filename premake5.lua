-- Copyright 2021 SMS
-- License(Apache-2.0)

print("\n")
print("   _____ _                           _   _            ")
print("  / ____| |                         | | (_)           ")
print(" | |    | | ___ _ __ ___   ___ _ __ | |_ _ _ __   ___ ")
print(" | |    | |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __| | '_ \\ / _ \\")
print(" | |____| |  __/ | | | | |  __/ | | | |_| | | | |  __/")
print("  \\_____|_|\\___|_| |_| |_|\\___|_| |_|\\__|_|_| |_|\\___|")
print("\n")

include "Thirdparty/premake/solution_items.lua"

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
thirdparty["stb"] = "%{wks.location}/Thirdparty/stb"
thirdparty["asio"] = "%{wks.location}/Thirdparty/asio"
thirdparty["entt"] = "%{wks.location}/Thirdparty/entt"
thirdparty["glad"] = "%{wks.location}/Thirdparty/glad"
thirdparty["glfw"] = "%{wks.location}/Thirdparty/glfw"
thirdparty["imgui"] = "%{wks.location}/Thirdparty/imgui"
thirdparty["spdlog"] = "%{wks.location}/Thirdparty/spdlog"
thirdparty["openal"] = "%{wks.location}/Thirdparty/openal"
thirdparty["vulkan"] = "%{wks.location}/Thirdparty/vulkan"
thirdparty["imguizmo"] = "%{wks.location}/Thirdparty/imguizmo"
thirdparty["tinygltf"] = "%{wks.location}/Thirdparty/tinygltf"
thirdparty["yaml_cpp"] = "%{wks.location}/Thirdparty/yaml_cpp"
thirdparty["tiny_obj_loader"] = "%{wks.location}/Thirdparty/tiny_obj_loader"
thirdparty["googletest"] = "%{wks.location}/Thirdparty/googletest/googletest"
thirdparty["nlohmann_json"] = "%{wks.location}/Thirdparty/nlohmann_json"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

include "Source"
include "Test"

group "Examples"
  include "Examples/Editor"
  include "Examples/2048"
  include "Examples/gobang"
  include "Examples/gamepad"
  include "Examples/minesweeper"
  include "Examples/pong"
  include "Examples/sort"
  include "Examples/sound"
group ""

group "Thirdparty"
    include "Thirdparty/glfw.lua"
    include "Thirdparty/glad.lua"
    include "Thirdparty/imgui.lua"
    include "Thirdparty/imguizmo.lua"
group""
