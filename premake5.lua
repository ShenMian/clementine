include "./thirdparty/premake/solution_items.lua"

workspace "Clementine"
  architecture "x86_64"
  startproject "Clementine"
  configurations {"Debug", "Release"}
  solution_items {".clang-format"}

	filter "configurations:Debug"
		defines {"DEBUG"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines {"NDEBUG"}
		runtime "Release"
		optimize "on"

thirdparty = {}
thirdparty["entt"] = "%{wks.location}/thirdparty/entt/include"
thirdparty["spdlog"] = "%{wks.location}/thirdparty/spdlog/include"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

include "src"
