# Copyright 2021 SMS
# License(Apache-2.0)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(editor ${SOURCES})

use_cpp20(editor)

target_include_directories(editor PUBLIC
	"${PROJECT_SOURCE_DIR}/Engine"
	"${DEPS_DIR}/Graphics/Source"
	"${DEPS_DIR}/Math/include"
	"${DEPS_DIR}/openal-soft/include")
target_link_libraries(editor PUBLIC clementine)
