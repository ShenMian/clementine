# Copyright 2020 SMS
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.5)

project("Clementine")

option(BUILD_EXAMPLES "Build examples"        ON)
option(BUILD_TESTS    "Build unit test files" ON)

set(CMAKE_CXX_STANDARD 14)

# 设置 lib 输出目录
set(LIBRARY_OUTPUT_PATH ../lib/)

include_directories("src")

add_subdirectory("thirdparty/SDL")
include_directories("thirdparty/SDL/include")

include_directories("thirdparty/spdlog/include")

include_directories("thirdparty/asio/asio/include")

add_subdirectory("src/clem")

# 例子
if(BUILD_EXAMPLES)
	add_subdirectory("examples")
endif()

# 单元测试
if(BUILD_TESTS)
  enable_testing()
	add_subdirectory("tests")
endif()

