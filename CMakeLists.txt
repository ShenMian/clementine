# Copyright 2020 SMS
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.5)

project("Clementine")

include_directories(".")

# 包含第三方库
include_directories("include")
link_directories("lib")

# 设置 lib 输出目录
set(LIBRARY_OUTPUT_PATH ../lib/)

set(CMAKE_CXX_STANDARD 14)

# 将 Clementine 编译到 lib 目录
add_subdirectory("clem")

# 包含 其他子项目
add_subdirectory("examples")
add_subdirectory("test")
