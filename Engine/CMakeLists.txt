# Copyright 2021 SMS
# License(Apache-2.0)

file(GLOB_RECURSE SOURCES "*.cpp")

add_library(clementine STATIC ${SOURCES})
add_library(clementine::clementine ALIAS clementine)

use_cpp20(clementine)

target_include_directories(clementine PUBLIC
	"${DEPS_DIR}/openal-soft/include"
	"${DEPS_DIR}/Graphics/Source"
	"${DEPS_DIR}/Math/include")
target_link_libraries(clementine PUBLIC graphics OpenAL)
