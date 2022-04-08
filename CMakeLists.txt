# Copyright 2021 SMS
# License(Apache-2.0)

# 指定最小版本号
cmake_minimum_required(VERSION 3.16)

# 指定项目名和版本号
project(Clementine
  VERSION     0.0.0
  DESCRIPTION "A simple game engine.")

# 选项
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS    "Build tests"    ON)

# 输出信息
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.22.0")
  cmake_host_system_information(RESULT OS_PRETTY_NAME QUERY DISTRIB_PRETTY_NAME)
endif()
message(STATUS "OS")
message(STATUS "|- Name   : ${CMAKE_SYSTEM_NAME}(${OS_PRETTY_NAME})")
message(STATUS "`- Version: ${CMAKE_SYSTEM_VERSION}")
message(STATUS "Compiler")
message(STATUS "|- ID     : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "`- Version: ${CMAKE_CXX_COMPILER_VERSION}")

# 指定默认编译类型
if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# 指定 Win32 下要定义的宏
if(WIN32)
  list(APPEND CLEMENTINE_DEFINES _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS UNICODE _UNICODE NOMINMAX)
endif()

if(MSVC)
  # 静态链接 MSVC 运行库
  set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if(UNIX)
  if(OS_PRETTY_NAME MATCHES "Ubuntu")
    set(UBUNTU true)
  endif()
  add_link_options("-ldl" "-lpthread")
endif()

macro(use_cpp20 TARGET)
    if(MSVC) # MSVC
        set_property(TARGET ${TARGET} PROPERTY
                CXX_STANDARD          23
                CXX_STANDARD_REQUIRED ON)
    elseif(APPLE) # AppleClang
        target_compile_options(${TARGET} PRIVATE -std=c++2a)
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU") # GCC/Clang
        set_property(TARGET ${TARGET} PROPERTY
                    CXX_STANDARD          20
                    CXX_STANDARD_REQUIRED ON)
    else()
        message(FATAL_ERROR "Unsupported compiler")
    endif()
endmacro()

set(DEPS_DIR "${PROJECT_SOURCE_DIR}/Deps")

add_subdirectory("${DEPS_DIR}/Graphics")

set(LIBTYPE STATIC)
add_subdirectory("${DEPS_DIR}/openal-soft")

add_subdirectory(Engine)
add_subdirectory(Editor)
