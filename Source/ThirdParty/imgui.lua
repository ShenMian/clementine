project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	files {
        "imgui/imgui/**.h",
        "imgui/imgui/*.cpp",

        "imgui/backends/imgui_impl_glfw.cpp",
        "imgui/backends/imgui_impl_opengl3.cpp"}
        -- "imgui/backends/imgui_impl_vulkan.cpp"}

	includedirs {
        "imgui",
        "%{deps.graphics}/ThirdParty/glfw/include",
        "%{deps.graphics}/ThirdParty/glad/include",
        "%{deps.graphics}/ThirdParty/Vulkan-Headers/include"}

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

  -- links "Graphics"
