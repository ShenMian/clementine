# Copyright 2020 SMS
# License(Apache-2.0)

# 添加 源文件
file(GLOB_RECURSE sources "*.cpp")

find_package(Threads REQUIRED)

# 创建 lib 库
add_library(clementine STATIC ${sources})
target_link_libraries(clementine PUBLIC Threads::Threads sdl2)

# if(CMAKE_SYSTEM_NAME MATCHES "Windows")
# 	file(GLOB PLATFORM_SOURCES "*.cpp")
# elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
# 	file(GLOB PLATFORM_SOURCES "*.cpp")
# endif()
