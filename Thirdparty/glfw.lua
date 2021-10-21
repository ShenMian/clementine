project "GLFW"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/lib")
	objdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

	files
	{
		"glfw/include/GLFW/glfw3.h",
		"glfw/include/GLFW/glfw3native.h",
		"glfw/src/glfw_config.h",
		"glfw/src/context.c",
		"glfw/src/init.c",
		"glfw/src/input.c",
		"glfw/src/monitor.c",
		"glfw/src/vulkan.c",
		"glfw/src/window.c"
	}

	links "msvcrtd"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		
		files
		{
			"glfw/src/platform.c",
			"glfw/src/null_init.c",

			"glfw/src/x11_*.c",
			"glfw/src/posix_*.c",
			"glfw/src/linux_*.c",
			"glfw/src/xkb_unicode.c",
			"glfw/src/glx_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/osmesa_context.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"glfw/src/platform.c",
			"glfw/src/null_*.c",
			"glfw/src/win32_*.c",
			"glfw/src/wgl_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"