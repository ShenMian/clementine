#!/bin/bash
# Copyright 2021 SMS
# License(Apache-2.0)

# 切换到主目录
cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd ..

# 创建build目录
if [ ! -d "./build" ]; then
	mkdir build
fi
cd build

git submodule update --init --recursive

# CMake构建
cmake ..
cmake --build .
