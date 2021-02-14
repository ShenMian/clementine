# Copyright 2020 SMS
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.5)

project("Clementine")

option(BUILD_TESTS    "Build unit test files" ON)
option(BUILD_EXAMPLES "Build examples"        ON)

set(CMAKE_CXX_STANDARD 14)

# 设置 lib 输出目录
set(LIBRARY_OUTPUT_PATH ../lib/)

include_directories(".")

# 将 Clementine 编译到 lib 目录
add_subdirectory("clem")

# 例子
if(BUILD_EXAMPLES)
	add_subdirectory("examples")
endif()

# 单元测试
if(BUILD_TESTS)
	# 添加 Google.Test
	include_directories("googletest/googletest/include")
	add_subdirectory("googletest")
	enable_testing()
	add_subdirectory("tests")
endif()

