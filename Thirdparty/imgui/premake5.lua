project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/lib")
	objdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

	files {
    "include/**.h",
    "src/**.cpp",
    "backends/**.h",
    "backends/imgui_impl_glfw.cpp",
    "backends/imgui_impl_opengl3.cpp",

    "premake5.lua"}

	includedirs {
        "include/imgui",
        "%{thirdparty.glad}/include",
        "%{thirdparty.glfw}/include"}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
