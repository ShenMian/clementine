# Copyright 2020 SMS
# License(Apache-2.0)

find_package(Threads REQUIRED)

file(GLOB_RECURSE sources "Clem/*.cpp")
link_directories("../thirdparty/openal/lib")

add_library(clementine STATIC ${sources})
target_link_libraries(clementine PUBLIC Threads::Threads)
