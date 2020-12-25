# Copyright 2020 SMS
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

project("Clementine")

# 添加 Google.Test
# include(cmake/googletest.cmake)
# fetch_googletest(
#  ${PROJECT_SOURCE_DIR}/cmake
#   ${PROJECT_BINARY_DIR}/googletest
# )

# 设置 编译选项
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")

# 设置 lib 输出目录
set(LIBRARY_OUTPUT_PATH ../lib/)

include_directories(".")

# 将 Clementine 编译到 lib 目录
add_subdirectory("clem")

# 包含其他子项目
add_subdirectory("examples")

# 单元测试
# enable_testing()
# add_subdirectory("test")
