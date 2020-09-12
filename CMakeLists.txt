# Copyright 2020 SMS
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.5)

project("Clementine")

include_directories(".")

# 包含 boost 库
include_directories("D:/Program Files/Program/boost_1_73_0")
link_directories("D:/Program Files/Program/boost_1_73_0/stage/lib")

# 设置 lib 输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_STANDARD 14)

# 将 Clementine 编译到 lib 目录
add_subdirectory("clem")

# 包含 其他子项目
link_directories("lib")
add_subdirectory("examples")
