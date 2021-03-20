-- Copyright 2021 SMS
-- License(Apache-2.0)

project "Clementine"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/bin")
  objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

  files {"**.h", "**.cpp"}

  includedirs {
    ".",
    "%{thirdparty.entt}",
    "%{thirdparty.spdlog}",
    "%{thirdparty.yaml_cpp}"}
