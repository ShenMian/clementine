project "Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"

    files {"**.cpp", "**.hpp", "**.h", "**.inl", "premake5.lua", "CMakeLists.txt"}

    includedirs {
        "../Engine",
        deps_inc["math"],
        deps_inc["graphics"]}

    links "Engine"

    filter "system:windows"
        links "%{deps_lib.steamworks}/win64/steam_api64"
        postbuildcommands "{COPYDIR} \"%{deps_lib.steamworks}/win64/steam_api64.dll\" \"%{cfg.targetdir}\""

    filter "system:linux"
        filter "platforms:x86"
            links "%{deps_lib.steamworks}/linux32/steam_api"
        filter "platforms:x64"
            links "%{deps_lib.steamworks}/linux64/steam_api"
    
    filter "system:mac"
        links "%{deps_lib.steamworks}/osx/steam_api"