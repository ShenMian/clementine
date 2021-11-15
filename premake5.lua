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
    deps["math"]     = "%{wks.location}/Source/ThirdParty/Math"
    deps["graphics"] = "%{wks.location}/Source/ThirdParty/Graphics"

    deps_include = {}
    deps_include["math"]     = "%{deps.math}/include"
    deps_include["graphics"] = "%{deps.graphics}/Source"

    include "Source/Engine"
    include "Source/Editor"

    group "ThirdParty"
        include "Source/ThirdParty/Graphics"
    group ""