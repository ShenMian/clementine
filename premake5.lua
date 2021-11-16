workspace "Clementine"
    architecture "x86_64"
    startproject "Editor"
    configurations {"Debug", "Release"}
    flags "MultiProcessorCompile"

    output_dir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"
    targetdir("%{wks.location}/build/" .. output_dir .. "/%{prj.name}/lib")
    objdir("%{wks.location}/build/" .. output_dir .. "/%{prj.name}/obj")

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
    deps["graphics"]   = "%{wks.location}/Source/ThirdParty/Graphics"
    deps["steamworks"] = "%{wks.location}/Source/ThirdParty/steamworks"

    deps_inc = {}
    deps_inc["math"]       = "%{deps.math}/include"
    deps_inc["graphics"]   = "%{deps.graphics}/Source"
    deps_inc["steamworks"] = "%{deps.steamworks}/public"

    deps_lib = {}
    deps_lib["steamworks"] = "%{deps.steamworks}/redistributable_bin"

    include "Source/Engine"
    include "Source/Editor"

    group "ThirdParty"
        externalproject "Graphics"
            location "%{deps.graphics}"
            kind "StaticLib"
    group ""