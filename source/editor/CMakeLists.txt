# Copyright 2022 SMS
# License(Apache-2.0)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(editor ${SOURCES})
target_compile_features(editor PRIVATE cxx_std_20)
target_include_directories(clementine PUBLIC
	"${PROJECT_SOURCE_DIR}/source/engine"
	"${PROJECT_SOURCE_DIR}/deps/Math"
	"${PROJECT_SOURCE_DIR}/deps/Graphics"
	"${PROJECT_SOURCE_DIR}/deps/Graphics/source/fmt")
target_link_libraries(editor PUBLIC clementine)
