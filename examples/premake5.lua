project "Examples"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  
  targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/bin")
  objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

  files {"**.h", "**.cpp"}

  includedirs {"%{wks.location}/src", "%{thirdparty.entt}", "%{thirdparty.spdlog}"}

  links {"Clementine"}
