# Copyright 2020 SMS
# License(Apache-2.0)

file(GLOB_RECURSE sources "Clem/*.cpp")

find_package(Threads REQUIRED)

add_library(clementine STATIC ${sources})
target_link_libraries(clementine PUBLIC Threads::Threads)
