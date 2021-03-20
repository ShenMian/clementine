include "./thirdparty/premake/solution_items.lua"

workspace "Clementine"
  architecture "x86_64"
  startproject "Examples"
  configurations {"Debug", "Release"}

  solution_items {
		".clang-format",
		"CMakeLists.txt",
		"premake5.lua"
	}

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
thirdparty["yaml_cpp"] = "%{wks.location}/thirdparty/yaml-cpp/include"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

include "src"
include "examples"
