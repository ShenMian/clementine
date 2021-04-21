# Copyright 2020 SMS
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.5)

project("Clementine")

set(CMAKE_CXX_STANDARD 17)

option(BUILD_EXAMPLES "Build examples"        ON)
option(BUILD_TESTS    "Build unit test files" OFF)

message("\n")
message("   _____ _                           _   _            ")
message("  / ____| |                         | | (_)           ")
message(" | |    | | ___ _ __ ___   ___ _ __ | |_ _ _ __   ___ ")
message(" | |    | |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __| | '_ \\ / _ \\")
message(" | |____| |  __/ | | | | |  __/ | | | |_| | | | |  __/")
message("  \\_____|_|\\___|_| |_| |_|\\___|_| |_|\\__|_|_| |_|\\___|")
message("\n")


# 设置 lib 输出目录
set(LIBRARY_OUTPUT_PATH ../lib/)

include_directories("Source")
include_directories("Thirdparty/asio/include")
include_directories("Thirdparty/entt/include")
include_directories("Thirdparty/spdlog/include")
include_directories("Thirdparty/openal/include")
include_directories("Thirdparty/yaml_cpp/include")

add_subdirectory("Thirdparty/yaml_cpp")
add_subdirectory("Source")

# 例子
if(BUILD_EXAMPLES)
	add_subdirectory("Examples")
endif()

# 单元测试
if(BUILD_TESTS)
  enable_testing()
	add_subdirectory("Tests")
endif()
