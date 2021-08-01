-- Copyright 2021 SMS
-- License(Apache-2.0)

project "Test"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++latest"
  staticruntime "on"
  
  targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/bin")
  objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

  files {"**.h", "**.cpp", "premake5.lua"}

  includedirs {
    "%{wks.location}/Source",
    "%{thirdparty.asio}/include",
    "%{thirdparty.entt}/include",
    "%{thirdparty.spdlog}/include",
    "%{thirdparty.openal}/include",
    "%{thirdparty.yaml_cpp}/include",
    "%{thirdparty.googletest}/include"}

  links {"Clementine"}
