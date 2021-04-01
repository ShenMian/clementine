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

  includedirs {
    ".",
    "%{thirdparty.sdl}/include",
    "%{thirdparty.entt}/include",
    "%{thirdparty.spdlog}/include",
    "%{thirdparty.openal}/include",
    "%{thirdparty.yaml_cpp}/include"}

  links {
    "yaml-cpp",
    "%{thirdparty.openal}/lib/openal32"}
