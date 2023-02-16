# Copyright 2023 ShenMian
# License(Apache-2.0)

enable_testing()

# 指定 Win32 下要定义的宏
if(WIN32)
    list(APPEND MATH_DEFINES _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS UNICODE _UNICODE NOMINMAX)
endif()

# 静态链接 MSVC 运行库
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if(UNIX)
    add_link_options("-ldl")
endif()

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(${PROJECT_NAME}_unit_test)

# find_package(OpenMP)
# if(OpenMP_CXX_FOUND)
#     target_link_libraries(unit_test PUBLIC OpenMP::OpenMP_CXX)
# endif()

target_link_libraries(${PROJECT_NAME}_unit_test PRIVATE clementine)
target_sources(${PROJECT_NAME}_unit_test PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME}_unit_test PRIVATE
    "${PROJECT_SOURCE_DIR}/deps/doctest"
    "${PROJECT_SOURCE_DIR}/deps/nanobench/src/include"
    "${PROJECT_SOURCE_DIR}/src/engine")
target_compile_features(${PROJECT_NAME}_unit_test PRIVATE cxx_std_20)

add_test(NAME unit_test COMMAND ../bin/${PROJECT_NAME}_unit_test)
add_test(NAME benchmark COMMAND ../bin/${PROJECT_NAME}_unit_test -ns -ts=benchmark)
