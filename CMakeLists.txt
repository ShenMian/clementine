# Copyright 2023 ShenMian
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(NOT DEFINED CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# SET(CMAKE_CXX_COMPILER_WORKS 1)

project(clementine
    VERSION      0.0.0
    DESCRIPTION  "A simple game engine."
    HOMEPAGE_URL "https://github.com/ShenMian/clementine"
    LANGUAGES    CXX C)

option(USE_CONAN   "Use conan" ON)
option(USE_VCPKG   "Use vcpkg" OFF)
option(BUILD_TESTS "Build tests" ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
endif()

include(scripts/display_info.cmake)

if(USE_CONAN AND EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

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

add_subdirectory(src/engine)
add_subdirectory(src/editor)
if(BUILD_TESTS )
    add_subdirectory(tests)
endif()
