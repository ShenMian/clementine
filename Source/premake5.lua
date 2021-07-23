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
    "%{thirdparty.sdl}/include",
    "%{thirdparty.asio}/include",
    "%{thirdparty.entt}/include",
    "%{thirdparty.glfw}/include",
    "%{thirdparty.spdlog}/include",
    "%{thirdparty.openal}/include",
    "%{thirdparty.yaml_cpp}/include",
    "%{thirdparty.nlohmann_json}/include"}

  links {
    "%{thirdparty.openal}/lib/openal32",
    "GLFW"}
