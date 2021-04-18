-- Copyright 2021 SMS
-- License(Apache-2.0)

project "Sound"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"
  
  targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/bin")
  objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

  files {"**.h", "**.cpp", "premake5.lua"}

  includedirs {
    "%{wks.location}/src",
    "%{thirdparty.asio}/include",
    "%{thirdparty.entt}/include",
    "%{thirdparty.spdlog}/include",
    "%{thirdparty.openal}/include",
    "%{thirdparty.yaml_cpp}/include"}

  links {"Clementine"}
