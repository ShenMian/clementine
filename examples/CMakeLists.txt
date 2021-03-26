# Copyright 2020 SMS
# License(Apache-2.0)

add_executable(minesweeper "minesweeper/minesweeper.cpp")
target_link_libraries(minesweeper clementine)

add_executable(pong "pong/pong.cpp")
target_link_libraries(pong clementine)
