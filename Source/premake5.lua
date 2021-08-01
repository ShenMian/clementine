-- Copyright 2021 SMS
-- License(Apache-2.0)

project "Clementine"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/lib")
  objdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

  files {"**.cpp", "**.h", "**.inl", "premake5.lua", "CMakeLists.txt"}

  filter "system:windows"
    links "xinput"

  defines {
    "USE_PROFILER",
    "USE_ASSERT"}

  includedirs {
    ".",
    "%{thirdparty.stb}/include",
    "%{thirdparty.sdl}/include",
    "%{thirdparty.asio}/include",
    "%{thirdparty.entt}/include",
    "%{thirdparty.glad}/include",
    "%{thirdparty.glfw}/include",
    "%{thirdparty.imgui}/include",
    "%{thirdparty.spdlog}/include",
    "%{thirdparty.openal}/include",
    "%{thirdparty.vulkan}/include",
    "%{thirdparty.yaml_cpp}/include",
    "%{thirdparty.nlohmann_json}/include"}

  links {
    "GLAD",
    "GLFW",
    "ImGui",
    "%{thirdparty.openal}/lib/openal32"}
