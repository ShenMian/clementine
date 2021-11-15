project "Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"

    files {"**.cpp", "**.hpp", "**.h", "**.inl", "premake5.lua", "CMakeLists.txt"}

    includedirs {
        deps_include["math"],
        deps_include["graphics"]}

    links {
        "Engine",
        "Graphics"}
