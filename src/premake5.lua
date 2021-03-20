-- Copyright 2021 SMS
-- License(Apache-2.0)

project "Clementine"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/bin")
  objdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

  files {"**.cpp", "**.h", "premake5.lua"}

  includedirs {
    ".",
    "%{thirdparty.entt}/include",
    "%{thirdparty.spdlog}/include",
    "%{thirdparty.yaml_cpp}/include"}

  links "yaml-cpp"
