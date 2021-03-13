# Copyright 2020 SMS
# License(Apache-2.0)

# 添加 Google.Test
include_directories("googletest/googletest/include")
add_subdirectory("googletest")

add_executable(math "math.cpp")
target_link_libraries(math gtest_main clementine)

add_test(
  NAME
    All
  COMMAND
    ${CMAKE_BINARY_DIR}/tests/math
)

