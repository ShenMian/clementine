project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/lib")
	objdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

	files {
        "imgui/include/imgui/**.h",
        "imgui/include/imgui/*.cpp",
        "imgui/include/imgui/backends/imgui_impl_glfw.cpp",
        "imgui/include/imgui/backends/imgui_impl_opengl3.cpp",
        "imgui/include/imgui/backends/imgui_impl_vulkan.cpp"}

	includedirs {
        "imgui/include/imgui",
        "%{thirdparty.glad}/include",
        "%{thirdparty.glfw}/include",
        "%{thirdparty.vulkan}/include"}

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
