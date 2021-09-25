project "ImGuizmo"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/lib")
	objdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

	files
	{
		"imguizmo/ImGuizmo.h",
		"imguizmo/ImGuizmo.cpp"
	}

	includedirs
	{
		"imguizmo",
    "%{thirdparty.imgui}/include/imgui"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"