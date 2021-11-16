project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"

    files {"**.cpp", "**.hpp", "**.h", "**.inl", "premake5.lua", "CMakeLists.txt"}

    includedirs {
        deps_inc["math"],
        deps_inc["graphics"],
        deps_inc["steamworks"]}
        
    links "Graphics"