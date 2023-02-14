# Copyright 2023 ShenMian
# License(Apache-2.0)

file(GLOB_RECURSE SOURCES "*.cpp")

add_library(clementine STATIC ${SOURCES})
add_library(clementine::clementine ALIAS clementine)

target_compile_features(clementine PRIVATE cxx_std_20)
target_compile_definitions(clementine PUBLIC ${CLEMENTINE_DEFINES})
target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/src/engine")

if(USE_VCPKG)
    # fmt
    find_package(fmt CONFIG REQUIRED)
    target_link_libraries(clementine PRIVATE fmt::fmt-header-only)

    # stb
    find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
    target_include_directories(clementine PRIVATE ${STB_INCLUDE_DIRS})

    # eastl
    find_package(EASTL CONFIG REQUIRED)
    target_link_libraries(clementine PRIVATE EASTL)

    # openal
    # find_package(OpenAL CONFIG REQUIRED)
    # target_link_libraries(clementine PRIVATE OpenAL::OpenAL)

    # freetype
    # find_package(Freetype REQUIRED)
    # target_link_libraries(clementine PRIVATE Freetype::Freetype) # since CMake 3.10
else()
    # fmt
    target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/deps/fmt/include")

    # math
    add_subdirectory("${PROJECT_SOURCE_DIR}/deps/math" "math")
    target_link_libraries(clementine PUBLIC math)

    # graphics
    set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples")
    add_subdirectory("${PROJECT_SOURCE_DIR}/deps/graphics" "graphics")
    target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/deps/graphics")
    target_link_libraries(clementine PUBLIC graphics)

    # stb
    target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/deps/stb")

    # openal
    set(LIBTYPE STATIC)
    add_subdirectory("${PROJECT_SOURCE_DIR}/deps/openal-soft" "openal-soft")
    target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/deps/openal-soft/include")
    target_link_libraries(clementine PUBLIC OpenAL)

    # libnyquist
    add_subdirectory("${PROJECT_SOURCE_DIR}/deps/libnyquist" "libnyquist")
    target_include_directories(clementine PUBLIC "${PROJECT_SOURCE_DIR}/deps/libnyquist/include")
    target_link_libraries(clementine PUBLIC libnyquist)

    # eastl
    # find_package(eastl)
    # target_link_libraries(clementine PUBLIC eastl::eastl)
endif()
