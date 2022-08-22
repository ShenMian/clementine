# Copyright 2021 SMS
# License(Apache-2.0)

file(GLOB_RECURSE SOURCES "*.cpp")

add_library(clementine STATIC ${SOURCES})
add_library(clementine::clementine ALIAS clementine)

target_link_libraries(clementine PUBLIC graphics)
target_compile_definitions(clementine PUBLIC ${CLEMENTINE_DEFINES})
target_compile_features(clementine PRIVATE cxx_std_20)
