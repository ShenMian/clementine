# Copyright 2022 SMS
# License(Apache-2.0)

file(GLOB_RECURSE SOURCES "*.cpp")

add_library(clementine STATIC ${SOURCES})
add_library(clementine::clementine ALIAS clementine)

target_compile_features(clementine PRIVATE cxx_std_20)
target_compile_definitions(clementine PUBLIC ${CLEMENTINE_DEFINES})
target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/src/engine")

# fmt
target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/deps/fmt/include")

# Math
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/Math" "Math")
target_link_libraries(clementine PUBLIC math)

# Graphics
set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples")
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/Graphics" "Graphics")
target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/deps/Graphics")
target_link_libraries(clementine PUBLIC graphics)

# OpenAL
set(LIBTYPE STATIC)
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/openal-soft" "openal-soft")
target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/deps/openal-soft/include")
target_link_libraries(clementine PUBLIC OpenAL)

# libnyquist
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/libnyquist" "libnyquist")
target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/deps/libnyquist/include")
target_link_libraries(clementine PUBLIC libnyquist)

# EASTL
# find_package(eastl)
# target_link_libraries(clementine PUBLIC eastl::eastl)