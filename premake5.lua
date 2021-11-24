workspace "Clementine"
    architecture "x86_64"
    startproject "Editor"
    flags "MultiProcessorCompile"

    -- 启用 OpenMP
    openmp "On"
    filter "toolset:not msc*"
        buildoptions "-fopenmp"

    output_dir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"
    targetdir("%{wks.location}/build/" .. output_dir .. "/%{prj.name}/lib")
    objdir("%{wks.location}/build/" .. output_dir .. "/%{prj.name}/obj")

    configurations {"Debug", "Release"}

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "on"

    deps = {}
    deps["math"]       = "%{wks.location}/Source/ThirdParty/Math"
    deps["imgui"]      = "%{wks.location}/Source/ThirdParty/imgui"
    deps["graphics"]   = "%{wks.location}/Source/ThirdParty/Graphics"
    deps["steamworks"] = "%{wks.location}/Source/ThirdParty/steamworks"

    deps_inc = {}
    deps_inc["math"]       = "%{deps.math}/include"
    deps_inc["imgui"]      = "%{deps.imgui}"
    deps_inc["graphics"]   = "%{deps.graphics}/Source"
    deps_inc["steamworks"] = "%{deps.steamworks}/public"

    deps_lib = {}
    deps_lib["steamworks"] = "%{deps.steamworks}/redistributable_bin"

    include "Source/Engine"
    include "Source/Editor"

    group "ThirdParty"
        include "Source/ThirdParty/imgui.lua"
    --[[
        externalproject "Graphics"
            location "%{deps.graphics}"
            kind "StaticLib"
    --]]
    group ""
