# Copyright 2021 SMS
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.16)

project(Clementine
    VERSION      0.0.0
    DESCRIPTION  "A simple game engine."
    HOMEPAGE_URL "https://github.com/ShenMian/Clementine"
    LANGUAGES    CXX C)

# 指定默认编译类型
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 默认生成 compilation databases
if(NOT DEFINED CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# 选项
option(USE_CONAN "Use conan" ON)

include(scripts/display_info.cmake)

if(USE_CONAN AND EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

# 指定库文件输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")

if(WIN32)
    list(APPEND CLEMENTINE_DEFINES _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS UNICODE _UNICODE NOMINMAX) # 指定 Win32 下要定义的宏
endif()

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") # 静态链接 MSVC 运行库
endif()

if(UNIX)
    if(OS_PRETTY_NAME MATCHES "Ubuntu")
        set(UBUNTU true)
    endif()
    add_link_options("-ldl" "-lpthread")
endif()

add_subdirectory(source/engine)
