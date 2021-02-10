# Copyright 2020 SMS
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TESTS    "Build unit test files" ON)
option(BUILD_EXAMPLES "Build examples" ON)

project(
	"Clementine"
	VERSION 0.0
	LANGUAGES CXX)

# 设置 编译选项
# set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS}")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")

# 设置 lib 输出目录
set(LIBRARY_OUTPUT_PATH ../lib/)

include_directories(".")

# 将 Clementine 编译到 lib 目录
add_subdirectory("clem")

# 例子
#if(BUILD_EXAMPLES)
	add_subdirectory("examples")
#endif()

# 单元测试
#if(BUILD_TESTS)
	# 添加 Google.Test
	include_directories("googletest/googletest/include")
	add_subdirectory("googletest")
	enable_testing()
	add_subdirectory("tests")
#endif()

