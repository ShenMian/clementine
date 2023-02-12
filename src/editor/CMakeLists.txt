# Copyright 2023 ShenMian
# License(Apache-2.0)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(editor ${SOURCES})
target_compile_features(editor PRIVATE cxx_std_20)
target_include_directories(editor PUBLIC
	"${PROJECT_SOURCE_DIR}/src/engine"
	"${PROJECT_SOURCE_DIR}/deps/Math"
	"${PROJECT_SOURCE_DIR}/deps/Graphics")
target_link_libraries(editor PUBLIC clementine)

file(COPY "shaders" DESTINATION "${CMAKE_BINARY_DIR}/bin")
