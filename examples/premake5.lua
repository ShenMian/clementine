-- Copyright 2021 SMS
-- License(Apache-2.0)

project "Examples"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"
  
  targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/bin")
  objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

  files {"**.h", "**.cpp"}

  includedirs {
    "%{wks.location}/src",
    "%{thirdparty.entt}",
    "%{thirdparty.spdlog}",
    "%{thirdparty.yaml_cpp}"}

  links {"Clementine"}
